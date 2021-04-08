#include "h265amdamfconfigurationdialog.h"
#include "ui_h265amdamfconfigurationdialog.h"

h265AMDAMFConfigurationDialog::h265AMDAMFConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::h265AMDAMFConfigurationDialog)
{
    ui->setupUi(this);

    /**
     * This Code deals with the Windows Size scaling
     */
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    /**
     * Ensures labels equal size
     */
    int maxWidth = 0;
    for (QLabel* label : findChildren<QLabel*>()) {
        if (maxWidth < label->width())
            maxWidth = label->width();
    }
    for (QLabel* label : findChildren<QLabel*>()) {
        if( label->objectName() != "h265_amd_amf_title_label"
                && label->objectName() != "h265_amd_amf_info_label" )
        label->setFixedWidth(maxWidth);
    }

    /**
      * Ensure buttons equal size
      */
    maxWidth = 0;
    for (QPushButton* btn : findChildren<QPushButton*>()) {
        if (maxWidth < btn->width())
            maxWidth = btn->width();
    }
    for (QPushButton* btn : findChildren<QPushButton*>()) {
        btn->setFixedWidth(maxWidth);
    }

    /*Initialize ui element values*/
    ui->h265_amd_amf_quality_combobox->addItems(ENCODER_QUALITY_OPT_LIST);

    ui->h265_amd_amf_rate_control_combobox->addItem(ENCODER_RATE_CONTROL_VBR_PEAK);

    ui->h265_amd_amf_max_bitrate_combobox->addItems(ENCODER_MAXRATE_OPT_LIST);


    config = new ConfigurationManager("/assets/h265AMDAMF.conf");
    entries_snapshot = QHash<QString, QString>();
    config->setEntry("file_apps", QCoreApplication::applicationDirPath() + "/assets/apps_windows.json");
    config->setEntry("file_state", QCoreApplication::applicationDirPath() + "/sunshine_state.json");
    config->saveConfiguration();

    setLoadedValues();
}

h265AMDAMFConfigurationDialog::~h265AMDAMFConfigurationDialog()
{
    delete ui;
}

void h265AMDAMFConfigurationDialog::setLoadedValues() {
    if(config->getKey("amf_quality") == ENCODER_QUALITY_SPEED) {
        ui->h265_amd_amf_quality_combobox->setCurrentIndex(0);
        entries_snapshot.insert("amf_quality", ENCODER_QUALITY_SPEED);
    }
    else if(config->getKey("amf_quality") == ENCODER_QUALITY_BALANCED) {
        ui->h265_amd_amf_quality_combobox->setCurrentIndex(1);
        entries_snapshot.insert("amf_quality", ENCODER_QUALITY_BALANCED);
    }
    else if(config->getKey("amf_quality") == ENCODER_QUALITY_QUALITY) {
        ui->h265_amd_amf_quality_combobox->setCurrentIndex(2);
        entries_snapshot.insert("amf_quality", ENCODER_QUALITY_QUALITY);
    }

    ui->h265_amd_amf_rate_control_combobox->setCurrentIndex(0);
    entries_snapshot.insert("amf_rc", ENCODER_RATE_CONTROL_VBR_PEAK);


    if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_5) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(0);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_5);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_10) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(1);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_10);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_15) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(2);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_15);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_20) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(3);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_20);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_25) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(4);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_25);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_30) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(5);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_30);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_35) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(6);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_35);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_40) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(7);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_40);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_45) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(8);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_45);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_50) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(9);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_50);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_55) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(10);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_55);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_60) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(11);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_60);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_65) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(12);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_65);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_70) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(13);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_70);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_75) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(14);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_75);
    }
    else if(config->getKey("amf_maxrate") == ENCODER_MAXRATE_80) {
        ui->h265_amd_amf_max_bitrate_combobox->setCurrentIndex(15);
        entries_snapshot.insert("amf_maxrate", ENCODER_MAXRATE_80);
    }
}

void h265AMDAMFConfigurationDialog::restoreDefaultsValues() {
    config->restoreDefaultConfiguration("/h265AMDAMF.conf");
}

void h265AMDAMFConfigurationDialog::on_h265_amd_amf_restore_button_clicked()
{
    restoreDefaultsValues();
    config->reloadInMemoryValues();
    config->setEntry("file_apps", QCoreApplication::applicationDirPath() + "/assets/apps_windows.json");
    config->setEntry("file_state", QCoreApplication::applicationDirPath() + "/sunshine_state.json");
    config->saveConfiguration();
    setLoadedValues();
    emit configuration_changed(h265AMDAMF);
}

void h265AMDAMFConfigurationDialog::on_h265_amd_amf_cancel_button_clicked()
{
    this->hide();
    //For cancel, restore loaded values
    this->setLoadedValues();
}



void h265AMDAMFConfigurationDialog::on_h265_amd_amf_ok_button_clicked()
{
    QString selected_quality = ui->h265_amd_amf_quality_combobox->currentText();
    config->setEntry("amf_quality", selected_quality);

    QString selected_rate_control = ui->h265_amd_amf_rate_control_combobox->currentText();
    config->setEntry("amf_rc", selected_rate_control);

    QString selected_max_rate = ui->h265_amd_amf_max_bitrate_combobox->currentText();
    if(selected_max_rate == ENCODER_MAXRATE_5_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_5);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_10_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_10);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_15_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_15);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_20_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_20);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_25_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_25);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_30_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_30);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_35_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_35);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_40_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_40);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_45_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_45);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_50_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_50);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_55_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_55);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_60_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_60);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_65_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_65);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_70_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_70);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_75_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_75);
    }
    else if(selected_max_rate == ENCODER_MAXRATE_80_LABEL) {
        config->setEntry("amf_maxrate", ENCODER_MAXRATE_80);
    }

    QString selected_gops_per_idr = ui->h265_gops_per_idr->text();
    config->setEntry("amf_gops_per_idr", selected_gops_per_idr);

    QString selected_g = ui->h265_g->text();
    config->setEntry("amf_g", selected_g);

    QString selected_rcs = ui->h265_rcs->text();
    config->setEntry("amf_rcs", selected_rcs);

    QString selected_qmin = ui->h265_qmin->text();
    config->setEntry("amf_qmin", selected_qmin);

    QString selected_qmax = ui->h265_qmax->text();
    config->setEntry("amf_qmax", selected_qmax);

    QString selected_b = ui->h265_b->text();
    config->setEntry("amf_b", selected_b);

    QString selected_maxrates = ui->h265_maxrates->text();
    config->setEntry("amf_maxrates", selected_maxrates);

    QString selected_bufsize = ui->h265_bufsize->text();
    config->setEntry("amf_bufsize", selected_bufsize);

    QString selected_min_qp_i = ui->h265_min_qp_i->text();
    config->setEntry("amf_min_qp_i", selected_min_qp_i);

    QString selected_max_qp_i = ui->h265_max_qp_i->text();
    config->setEntry("amf_max_qp_i", selected_max_qp_i);

    QString selected_min_qp_p = ui->h265_min_qp_p->text();
    config->setEntry("amf_min_qp_p", selected_min_qp_p);

    QString selected_max_qp_p = ui->h265_max_qp_p->text();
    config->setEntry("amf_max_qp_p", selected_max_qp_p);

    QString selected_qp = ui->h265_level->text();
    config->setEntry("amf_level", selected_qp);

    QString selected_header_insertion_mode = ui->h265_header_insertion_mode->text();
    config->setEntry("amf_header_insertion_mode", selected_header_insertion_mode);

    if(entries_snapshot.value("amf_quality") != config->getKey("amf_quality") ||
       entries_snapshot.value("amf_rc") != config->getKey("amf_rc") ||
       entries_snapshot.value("amf_maxrate") != config->getKey("amf_maxrate") ||
       entries_snapshot.value("amf_gops_per_idr") != config->getKey("amf_gops_per_idr") ||
       entries_snapshot.value("amf_g") != config->getKey("amf_g") ||
       entries_snapshot.value("amf_rcs") != config->getKey("amf_rcs") ||
       entries_snapshot.value("amf_qmin") != config->getKey("amf_qmin") ||
       entries_snapshot.value("amf_qmax") != config->getKey("amf_qmax") ||
       entries_snapshot.value("amf_b") != config->getKey("amf_b") ||
       entries_snapshot.value("amf_maxrates") != config->getKey("amf_maxrates") ||
       entries_snapshot.value("amf_bufsize") != config->getKey("amf_bufsize") ||
       entries_snapshot.value("amf_min_qp_i") != config->getKey("amf_min_qp_i") ||
       entries_snapshot.value("amf_max_qp_i") != config->getKey("amf_max_qp_i") ||
       entries_snapshot.value("amf_min_qp_p") != config->getKey("amf_min_qp_p") ||
       entries_snapshot.value("amf_max_qp_p") != config->getKey("amf_max_qp_p") ||
       entries_snapshot.value("amf_level") != config->getKey("amf_level") ||
       entries_snapshot.value("amf_header_insertion_mode") != config->getKey("amf_header_insertion_mode")
      ) {
         config->saveConfiguration();
         entries_snapshot.insert("amf_quality", config->getKey("amf_quality"));
         entries_snapshot.insert("amf_rc", config->getKey("amf_rc"));
         entries_snapshot.insert("amf_maxrate", config->getKey("amf_maxrate"));
         entries_snapshot.insert("amf_gops_per_idr", config->getKey("amf_gops_per_idr"));
         entries_snapshot.insert("amf_g", config->getKey("amf_g"));
         entries_snapshot.insert("amf_rcs", config->getKey("amf_rcs"));
         entries_snapshot.insert("amf_qmin", config->getKey("amf_qmin"));
         entries_snapshot.insert("amf_qmax", config->getKey("amf_qmax"));
         entries_snapshot.insert("amf_b", config->getKey("amf_b"));
         entries_snapshot.insert("amf_maxrates", config->getKey("amf_maxrates"));
         entries_snapshot.insert("amf_bufsize", config->getKey("amf_bufsize"));
         entries_snapshot.insert("amf_min_qp_i", config->getKey("amf_min_qp_i"));
         entries_snapshot.insert("amf_max_qp_i", config->getKey("amf_max_qp_i"));
         entries_snapshot.insert("amf_min_qp_p", config->getKey("amf_min_qp_p"));
         entries_snapshot.insert("amf_max_qp_p", config->getKey("amf_max_qp_p"));
         entries_snapshot.insert("amf_level", config->getKey("amf_level"));
         entries_snapshot.insert("amf_header_insertion_mode", config->getKey("amf_header_insertion_mode"));
         emit configuration_changed(h265AMDAMF);
    }
    this->hide();
}
