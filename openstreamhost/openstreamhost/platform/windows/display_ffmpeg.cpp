#include "openstreamhost/main.h"
#include "display.h"

extern "C" {
#include <libavdevice/avdevice.h>
#include <libavutil/pixdesc.h>
}

using namespace platf;
using namespace platf::dxgi;

#define USE_GDIGRAB

#if defined (USE_GDIGRAB)
static constexpr const char *kInputFormat = "gdigrab";
static constexpr const char *kInputDevice = "desktop";
#elif defined(USE_DSHOW)
static constexpr const char *kInputFormat = "dshow";
//static constexpr const char *kInputDevice = "video=screen-capture-recorder";
static constexpr const char *kInputDevice = "video=UScreenCapture";
#endif

display_ffmpeg_t::display_ffmpeg_t()
    : av_fmt_ctx(nullptr), av_codec_ctx(nullptr),
      current_frame(nullptr),
      row_pitch(0), video_stream_index(-1)
{}

capture_e display_ffmpeg_t::snapshot(img_t *img, std::chrono::milliseconds timeout, bool cursor_visible)
{
  if (read_frame() == 0) {
    img->width = width;
    img->height = height;
    img->row_pitch = row_pitch;
    std::copy_n(current_frame->data[0], width * height * 4, img->data);
    return capture_e::ok;
  }

  return capture_e::error;
}

std::shared_ptr<img_t> display_ffmpeg_t::alloc_img()
{
  auto img = std::make_shared<img_t>();

  img->pixel_pitch  = 4;
  img->row_pitch    = row_pitch;
  img->width        = width;
  img->height       = height;
  img->data         = new std::uint8_t[img->row_pitch * height];

  return img;
}

int display_ffmpeg_t::dummy_img(img_t * /* img_base */)
{
    return 0;
}

int display_ffmpeg_t::init()
{    
  av_register_all();
  avdevice_register_all();
  avcodec_register_all();
  av_log_set_level(AV_LOG_DEBUG);
  video_stream_index = -1;
  row_pitch = 4;
  int ret = 0;
  AVInputFormat *ifmt = av_find_input_format(kInputFormat);

  if (ifmt == nullptr) {
      BOOST_LOG(error) << "Could not find input format [" << kInputFormat << "]";
      return -1;
  }

  AVDictionary *opts = nullptr;
  av_dict_set(&opts, "probesize", "42M", 0);

  if(avformat_open_input(&av_fmt_ctx, kInputDevice, ifmt, &opts) != 0){
    BOOST_LOG(error) << "Couldn't open input device [" << kInputDevice << "] for input format [" << kInputFormat << "]";
    return -1;
  }

  av_dict_free(&opts);

  if (avformat_find_stream_info(av_fmt_ctx, nullptr) < 0) {
    BOOST_LOG(error) << "Couldn't find stream info for input device [" << kInputDevice << "] of input format [" << kInputFormat << "]";
    return -1;
  }

  for (unsigned int i = 0; i < av_fmt_ctx->nb_streams; i++) {
    if (av_fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      /// TODO: cast from unsigned to signed
      /// may be something like intialized flag is better?
      video_stream_index = i;
      break;
    }
  }

  if (video_stream_index == -1) {
    BOOST_LOG(error) << "Could not find video stream for input device [" << kInputDevice << "] of input format [" << kInputFormat << "]";
    return -1;
  }

  AVCodecID decoder_id = av_fmt_ctx->streams[video_stream_index]->codecpar->codec_id;
  AVCodec* decoder = avcodec_find_decoder(decoder_id);

  if (decoder == nullptr) {
    BOOST_LOG(error) << "Could not find video decoder [" << avcodec_get_name(decoder_id) << "]";
    return -1;
  }

  av_codec_ctx = avcodec_alloc_context3(decoder);

  if (av_codec_ctx == nullptr) {
    BOOST_LOG(error) << "Could not alloc context for video decoder [" << decoder->name << "]";
    return -1;
  }

  if (avcodec_open2(av_codec_ctx, decoder, nullptr) != 0) {
    BOOST_LOG(error) << "Could not open video decoder [" << decoder->name << "]";
    return -1;
  }

  current_frame = av_frame_alloc();

  if (current_frame == nullptr) {
      BOOST_LOG(error) << "Couldn't alloc frame";
      return -1;
  }

  log_flush();

  ret = read_frame();
  return ret;
}

void display_ffmpeg_t::release()
{
  if (av_fmt_ctx != nullptr) {
    avformat_close_input(&av_fmt_ctx);
    av_fmt_ctx = nullptr;
  }

  if (av_codec_ctx != nullptr) {
    avcodec_close(av_codec_ctx);
    avcodec_free_context(&av_codec_ctx);
    av_codec_ctx = nullptr;
  }

  if (current_frame != nullptr) {
    av_frame_free(&current_frame);
    current_frame = nullptr;
  }

  video_stream_index = -1;
  row_pitch = 0;
}

display_ffmpeg_t::~display_ffmpeg_t()
{
  release();
}


int display_ffmpeg_t::read_frame()
{
  AVPacket packet;
  av_init_packet(&packet);
  int ret = 0;

  if ((ret = av_read_frame(av_fmt_ctx, &packet)) < 0) {
    BOOST_LOG(error) << "Could not read frame [" << error_message(ret) + "]";
    goto out;
  }

  if ((ret = avcodec_send_packet(av_codec_ctx, &packet)) == 0) {
    if ((ret = avcodec_receive_frame(av_codec_ctx, current_frame)) == 0) {
       row_pitch = current_frame->linesize[0];
       width = current_frame->width;
       height = current_frame->height;
    } else {
      BOOST_LOG(error) << "Could not receive frame [" << error_message(ret) + "]";
    }
  } else {
    BOOST_LOG(error) << "Could not send packet [" << error_message(ret) + "]";
  }

out:
  av_packet_unref(&packet);
  return ret;
}

std::string display_ffmpeg_t::error_message(int code)
{
    std::string str;
    str.reserve(AV_ERROR_MAX_STRING_SIZE);
    av_make_error_string(str.data(), AV_ERROR_MAX_STRING_SIZE, code);
    return str;
}
