#include "Raspbed.hpp"

Raspbed::Raspbed(QWidget *parent) : QMainWindow(parent), ui(new Ui::Raspbed), bed() {
    ui->setupUi(this);
    settings.loadSettings();

    setupDisplay();

    settingsMenu = ui->menuBar->addMenu("Menu");
    settingsAction = settingsMenu->addAction("Settings");

    connect( settingsAction, SIGNAL( triggered() ), this, SLOT( openSettings() ) );

    selectedButton = ui->headUpButton;
    selected = false;

    numRightClicks = 0;
    numLeftClicks = 0;
}

Raspbed::~Raspbed() { delete ui; }

QPushButton* Raspbed::nextButton(){
    if(selectedButton == ui->headUpButton) { // Set correct button
        return ui->headDownButton;
    }else if(selectedButton == ui->headDownButton){
        return ui->feetUpButton;
    }else if(selectedButton == ui->feetUpButton){
        return ui->feetDownButton;
    }else if(selectedButton == ui->feetDownButton){
        return ui->trendButton;
    }else if(selectedButton == ui->trendButton){
        return ui->bedUpButton;
    }else if(selectedButton == ui->bedUpButton){
        return ui->bedDownButton;
    }else if(selectedButton == ui->bedDownButton){
        return ui->lowerWheelsButton;
    }else{
        return ui->headUpButton;
    }
}
void Raspbed::resetClicks(){
    numRightClicks = 0;
    numLeftClicks = 0;
    qDebug() << "Reset Clicks";
}


/**
 * Common method called for button and window events when not in buttonmode.
 * @brief Raspbed::mouseEvent
 * @param event
 */
void Raspbed::mouseSelectEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if( numRightClicks > 0){
            numLeftClicks++;
            qDebug() << "Pressed Left Click, R=" << QString::number(numRightClicks)
                << ", L=" << QString::number(numLeftClicks);
        }

        selected = false;
        selectedButton->setStyleSheet("");
        selectedButton = nextButton();
        selectedButton->setStyleSheet("border: 3px solid white");
    } else if (event->button() == Qt::RightButton){
        QTimer::singleShot(500, this, SLOT(resetClicks()));
        numRightClicks++;

        if( (numRightClicks >= 2) && (numLeftClicks >= 1) ){
            on_callButton_clicked();
        }

        if(selected){
            if(selectedButton == ui->headUpButton) { // Set correct button
                headUpHoldButton();
            }else if(selectedButton == ui->headDownButton){
                headDownHoldButton();
            }else if(selectedButton == ui->feetUpButton){
                feetUpHoldButton();
            }else if(selectedButton == ui->feetDownButton){
                feetDownHoldButton();
            }else if(selectedButton == ui->trendButton){
                trendHoldButton();
            }else if(selectedButton == ui->bedUpButton){
                bedUpHoldButton();
            }else if(selectedButton == ui->bedDownButton){
                bedDownHoldButton();
            }else if(selectedButton == ui->lowerWheelsButton){
                lowerWheelsHoldButton();
            }else{
                qDebug() << "Error, button doesn't exist.";
            }
        }

        selectedButton->setStyleSheet("background-color: white");
        selected = true;
        qDebug() << "Pressed Right Click, R=" << QString::number(numRightClicks)
               << ", L=" << QString::number(numLeftClicks);

    }
}

/**
 * Event filter for window. Only applied if not in button mode
 * @brief Raspbed::mousePressEvent
 * @param event
 */
void Raspbed::mousePressEvent(QMouseEvent * event){
    if(!settings.isButtonMode() /* &&  bed.getSerialPort()->isConnected()*/){
        mouseSelectEvent(event);
    }
}

/**
 * Event filter for buttons. Only applied if not in button mode.
 * @brief Raspbed::eventFilter
 * @param object
 * @param event
 * @return
 */
bool Raspbed::eventFilter(QObject *object, QEvent *event)
{
    if(!settings.isButtonMode() /* &&  bed.getSerialPort()->isConnected()*/){
        if (( event->type() == QEvent::MouseButtonPress)) {
            mouseSelectEvent(static_cast<QMouseEvent *>(event));
            return true;
        }
    }
    return QWidget::eventFilter(object,event);
}

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
    settingsDialog->setButtonMode(settings.isButtonMode());
    settingsDialog->setButtonHoldTime(QString::number(settings.getButtonHoldTime()));
    settingsDialog->populateSettings();
    settingsDialog->exec();

    if (settingsDialog->result() == QDialog::Accepted){
        settings.setContact(settingsDialog->getContact());
        settings.setPort(settingsDialog->getPort());
        settings.setBordered(settingsDialog->isBordered());
        settings.setButtonMode(settingsDialog->isButtonMode());
        settings.setButtonHoldTime(settingsDialog->getButtonHoldTime().toInt());
        settings.saveSettings();

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
        QString errorMessage = "WARNING: No serial port open. Failure opening " + settings.getPort();
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

    if(!settings.isButtonMode()){
        selectedButton = ui->headUpButton;
        selectedButton->setStyleSheet("border: 3px solid white");
    }
}

void Raspbed::setupButtons(){
    QList<QPushButton *> allPButtons = ui->centralWidget->findChildren<QPushButton *>();

    for(auto button : allPButtons){
        button->setIconSize(headUpPixmap.rect().size());
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        if(!bed.getSerialPort()->isConnected()){
            if(!settings.isButtonMode()){// Buttons disabled, disable skype
                button->setEnabled(false);
                button->installEventFilter(this);
            } else { // Buttons Enabled, leave skype enabled
                if(button != ui->callButton) {
                    button->setEnabled(false);
                } else {
                    button->setEnabled(true);
                }
            }
            ui->statusBar->showMessage("WARNING: No serial port detected.");
        } else {
            if(!settings.isButtonMode()){// Buttons disabled
                button->setEnabled(false);
                button->installEventFilter(this);
            } else {
                button->setEnabled(true);
            }
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
    bed.command(bed.relay.head_down, true);
    ui->statusBar->showMessage("Lowering head of bed...");
}

void Raspbed::on_headDownButton_released() {

    bed.command(bed.relay.head_down, false);
    ui->statusBar->showMessage("");
}

void Raspbed::headDownHoldButton(){
    bed.command(bed.relay.head_down, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.head_down, false);
}

void Raspbed::on_headUpButton_pressed() {
    bed.command(bed.relay.head_up, true);
    ui->statusBar->showMessage("Raising head of bed...");
}

void Raspbed::on_headUpButton_released() {
    bed.command(bed.relay.head_up, false);
    ui->statusBar->showMessage("");
}

void Raspbed::headUpHoldButton(){
    bed.command(bed.relay.head_up, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.head_up, false);
}

void Raspbed::on_feetUpButton_pressed() {
    bed.command(bed.relay.feet_up, true);
    ui->statusBar->showMessage("Raising foot of bed...");
}

void Raspbed::on_feetUpButton_released() {
    bed.command(bed.relay.feet_up, false);
    ui->statusBar->showMessage("");
}

void Raspbed::feetUpHoldButton(){
    bed.command(bed.relay.feet_up, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.feet_up, false);
}

void Raspbed::on_feetDownButton_pressed() {
    bed.command(bed.relay.feet_down, true);
    ui->statusBar->showMessage("Lowering foot of bed...");
}

void Raspbed::on_feetDownButton_released() {
    bed.command(bed.relay.feet_down, false);
    ui->statusBar->showMessage("");
}

void Raspbed::feetDownHoldButton(){
    bed.command(bed.relay.feet_down, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.feet_down, false);
}

void Raspbed::on_trendButton_pressed() {
    bed.command(bed.relay.trend_up, true);
    ui->statusBar->showMessage("Trending bed...");
}

void Raspbed::on_trendButton_released() {
    bed.command(bed.relay.trend_up, false);
    ui->statusBar->showMessage("");
}

void Raspbed::trendHoldButton(){
    bed.command(bed.relay.trend_up, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.trend_up, false);
}

void Raspbed::on_bedUpButton_pressed() {
    bed.command(bed.relay.bed_up, true);
    ui->statusBar->showMessage("Raising bed...");
}

void Raspbed::on_bedUpButton_released() {
    bed.command(bed.relay.bed_up, false);
    ui->statusBar->showMessage("");
}

void Raspbed::bedUpHoldButton(){
    bed.command(bed.relay.bed_up, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.bed_up, false);
}

void Raspbed::on_bedDownButton_pressed() {
    bed.command(bed.relay.bed_down, true);
    ui->statusBar->showMessage("Lowering bed...");
}

void Raspbed::on_bedDownButton_released() {
    bed.command(bed.relay.bed_down, false);
    ui->statusBar->showMessage("");
}

void Raspbed::bedDownHoldButton(){
    bed.command(bed.relay.bed_down, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.bed_down, false);
}

void Raspbed::on_lowerWheelsButton_pressed() {
    bed.command(bed.relay.lower_wheels, true);
    bed.command(bed.relay.bed_down, true);
    ui->statusBar->showMessage("Lowering wheels...");
}

void Raspbed::on_lowerWheelsButton_released() {
    bed.command(bed.relay.lower_wheels, false);
    bed.command(bed.relay.bed_down, false);
    ui->statusBar->showMessage("");
}

void Raspbed::lowerWheelsHoldButton(){
    bed.command(bed.relay.lower_wheels, true);
    bed.command(bed.relay.bed_down, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.lower_wheels, false);
    bed.command(bed.relay.bed_down, false);
}

void Raspbed::on_flattenBedButton_clicked(){
    ui->statusBar->showMessage("Flattening bed", 20000);
    bed.command(bed.relay.head_down, true);
    bed.command(bed.relay.feet_down, true);
    sleep(20);
    bed.command(bed.relay.head_down, false);
    bed.command(bed.relay.feet_down, false);
}

void Raspbed::on_callButton_clicked()
{
    qDebug() << "Calling " << settings.getContact();
    QString message = "Calling skype contact " + settings.getContact();
    ui->statusBar->showMessage(message,10000);
    std::string skypeCommand = "skype --callto " + settings.getContact().toStdString() + " &";
    system(skypeCommand.c_str());
}
