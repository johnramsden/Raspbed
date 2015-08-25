#include "Raspbed.hpp"

Raspbed::Raspbed(QWidget *parent) : QMainWindow(parent), ui(new Ui::Raspbed), bed() {
    ui->setupUi(this);

//    settings.setContact("+16049263981");
//    settings.setBordered(true);
//    settings.setPort("ttyUSB0");


    setupDisplay();

    settingsMenu = ui->menuBar->addMenu("Menu");
    settingsAction = settingsMenu->addAction("Settings");

    connect( settingsAction, SIGNAL( triggered() ), this, SLOT( openSettings() ) );
}

Raspbed::~Raspbed() { delete ui; }

void Raspbed::openSettings(){
    Settings *settingsDialog = new Settings();

    QStringList serialPortOptions;
    for(std::string device : bed.getSerialPort()->getDevices()) {
        qDebug() << "Serial option: " << QString::fromStdString(device);
        serialPortOptions.push_back(QString::fromStdString(device));
    }

    settingsDialog->setSerialPorts(serialPortOptions);
    settingsDialog->setPort(settings.getPort());
    settingsDialog->setContact(settings.getContact());
    settingsDialog->setBordered(settings.isBordered());
    settingsDialog->populateSettings();
    settingsDialog->exec();

   if (settingsDialog->result() == QDialog::Accepted){
       settings.setContact(settingsDialog->getContact());
       settings.setPort(settingsDialog->getPort());
       settings.setBordered(settingsDialog->isBordered());

       qDebug() << "\nChanged Settings to:";
       qDebug() << settings.getContact();
       qDebug() << settings.getPort();
       qDebug() << settings.isBordered();

       setupDisplay();

       resetBed();
   }
}

void Raspbed::resetBed(){
    qDebug() << "Stopping serialport to change settings";
    bed.getSerialPort()->stop();
    bed.getSerialPort()->setPortName(settings.getPort().toStdString());
    qDebug() << "Reopening port with " << settings.getPort();
    if(!bed.getSerialPort()->open()){
        setupButtons();
        QString errorMessage = "WARNING: No Serial Port open. Failure opening " + settings.getPort();
        ui->statusBar->showMessage(errorMessage);
    }
}

void Raspbed::setupDisplay(){

    setupIconBorders();

    QIcon headUpButtonIcon(headUpPixmap);
    ui->headUpButton->setIcon(headUpButtonIcon);

    QIcon headDownButtonIcon(headDownPixmap);
    ui->headDownButton->setIcon(headDownButtonIcon);

    QIcon feetUpButtonIcon(feetUpPixmap);
    ui->feetUpButton->setIcon(feetUpButtonIcon);

    QIcon feetDownButtonIcon(feetDownPixmap);
    ui->feetDownButton->setIcon(feetDownButtonIcon);

    QIcon trendButtonIcon(trendPixmap);
    ui->trendButton->setIcon(trendButtonIcon);

    QIcon bedUpButtonIcon(bedUpPixmap);
    ui->bedUpButton->setIcon(bedUpButtonIcon);

    QIcon bedDownButtonIcon(bedDownPixmap);
    ui->bedDownButton->setIcon(bedDownButtonIcon);

    QIcon lowerWheelsButtonIcon(lowerWheelsPixmap);
    ui->lowerWheelsButton->setIcon(lowerWheelsButtonIcon);

    QIcon flattenBedButtonIcon(flattenBedPixmap);
    ui->flattenBedButton->setIcon(flattenBedButtonIcon);

    QIcon callButtonIcon(callPixmap);
    ui->callButton->setIcon(callButtonIcon);

    setupButtons();
}

void Raspbed::setupButtons(){
    QList<QPushButton *> allPButtons = ui->centralWidget->findChildren<QPushButton *>();

    for(auto button : allPButtons){
        button->setIconSize(headUpPixmap.rect().size());
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        if(!bed.getSerialPort()->isConnected()){
            if(button != ui->callButton) { button->setEnabled(false); }
            ui->statusBar->showMessage("WARNING: No serial port detected.");
        } else {
            button->setEnabled(true);
            ui->statusBar->showMessage("Connected to port.");
        }
    }
}

void Raspbed::setupIconBorders(){
    if(settings.isBordered()){
        headUpPixmap =  QPixmap("images/border/headUpButton.png");
        headDownPixmap =  QPixmap("images/border/headDownButton.png");
        feetUpPixmap =  QPixmap("images/border/feetUpButton.png");
        feetDownPixmap =  QPixmap("images/border/feetDownButton.png");
        trendPixmap =  QPixmap("images/border/trendButton.png");
        bedUpPixmap =  QPixmap("images/border/bedUpButton.png");
        bedDownPixmap =  QPixmap("images/border/bedDownButton.png");
        lowerWheelsPixmap =  QPixmap("images/border/lowerWheelsButton.png");
        flattenBedPixmap =  QPixmap("images/border/flattenButton.png");
        callPixmap =  QPixmap("images/border/callButton.png");
    } else {
        headUpPixmap =  QPixmap("images/no-border/headUpButton.png");
        headDownPixmap =  QPixmap("images/no-border/headDownButton.png");
        feetUpPixmap =  QPixmap("images/no-border/feetUpButton.png");
        feetDownPixmap =  QPixmap("images/no-border/feetDownButton.png");
        trendPixmap =  QPixmap("images/no-border/trendButton.png");
        bedUpPixmap =  QPixmap("images/no-border/bedUpButton.png");
        bedDownPixmap =  QPixmap("images/no-border/bedDownButton.png");
        lowerWheelsPixmap =  QPixmap("images/no-border/lowerWheelsButton.png");
        flattenBedPixmap =  QPixmap("images/no-border/flattenButton.png");
        callPixmap =  QPixmap("images/no-border/callButton.png");
    }
}

void Raspbed::on_headDownButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.head_down, true);
        ui->statusBar->showMessage("Lowering head of bed...");
    }
}

void Raspbed::on_headDownButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.head_down, false);
        ui->statusBar->showMessage("");
    }
}

void Raspbed::on_headUpButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.head_up, true);
        ui->statusBar->showMessage("Raising head of bed...");
    }
}

void Raspbed::on_headUpButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.head_up, false);
        ui->statusBar->showMessage("");
    }
}

void Raspbed::on_feetUpButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.feet_up, true);
        ui->statusBar->showMessage("Raising foot of bed...");
            }
}

void Raspbed::on_feetUpButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.feet_up, false);
        ui->statusBar->showMessage("");
    }
}

void Raspbed::on_feetDownButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.feet_down, true);
        ui->statusBar->showMessage("Lowering foot of bed...");
    }
}

void Raspbed::on_feetDownButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.feet_down, false);
        ui->statusBar->showMessage("");
    }
}

void Raspbed::on_trendButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.trend_up, true);
        ui->statusBar->showMessage("Trending bed...");
    }
}

void Raspbed::on_trendButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.trend_up, false);
        ui->statusBar->showMessage("");
    }
}

void Raspbed::on_bedUpButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.bed_up, true);
        ui->statusBar->showMessage("Raising bed...");
    }
}

void Raspbed::on_bedUpButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.bed_up, false);
        ui->statusBar->showMessage("");
    }
}

void Raspbed::on_bedDownButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.bed_down, true);
        ui->statusBar->showMessage("Lowering bed...");
    }
}

void Raspbed::on_bedDownButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.bed_down, false);
        ui->statusBar->showMessage("");
    }
}

void Raspbed::on_lowerWheelsButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
    bed.command(bed.relay.lower_wheels, true);
    bed.command(bed.relay.bed_down, true);
    ui->statusBar->showMessage("Lowering wheels...");
    }
}

void Raspbed::on_lowerWheelsButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.lower_wheels, false);
        bed.command(bed.relay.bed_down, false);
        ui->statusBar->showMessage("");
    }
}

void Raspbed::on_flattenBedButton_clicked(){
    if(bed.getSerialPort()->isConnected()){
        ui->statusBar->showMessage("Flattening bed", 20000);
        bed.command(bed.relay.head_down, true);
        bed.command(bed.relay.feet_down, true);
        sleep(20);
        bed.command(bed.relay.head_down, false);
        bed.command(bed.relay.feet_down, false);
    }
}

void Raspbed::on_callButton_clicked()
{
    qDebug() << "Calling " << settings.getContact();
    QString message = "Calling skype contact " + settings.getContact();
    ui->statusBar->showMessage(message,10000);
    std::string skypeCommand = "skype --callto " + settings.getContact().toStdString() + " &";
    system(skypeCommand.c_str());
}
