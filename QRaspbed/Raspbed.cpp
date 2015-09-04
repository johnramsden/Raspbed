#include "Raspbed.hpp"


Raspbed::Raspbed(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Raspbed), bed() {
    ui->setupUi(this);
    settings.loadSettings();

    setupDisplay();

    settingsMenu = ui->menuBar->addMenu("Menu");
    settingsAction = settingsMenu->addAction("Settings");

    connect(settingsAction, SIGNAL(triggered()), this, SLOT(openSettings()));

    selectedButton = ui->headUpButton;
    selected = false;
    callInProgress = false;
    numRightClicks = 0;
    numLeftClicks = 0;

    resetBed();
}

Raspbed::~Raspbed() { delete ui; }

/**
 * @brief Raspbed::nextButton
 * @return
 */
QPushButton *Raspbed::nextButton() {
    if (selectedButton == ui->headUpButton) { // Set correct button
        return ui->headDownButton;
    } else if (selectedButton == ui->headDownButton) {
        return ui->feetUpButton;
    } else if (selectedButton == ui->feetUpButton) {
        return ui->feetDownButton;
    } else if (selectedButton == ui->feetDownButton) {
        return ui->trendButton;
    } else if (selectedButton == ui->trendButton) {
        return ui->bedUpButton;
    } else if (selectedButton == ui->bedUpButton) {
        return ui->bedDownButton;
    } else if (selectedButton == ui->bedDownButton) {
        return ui->lowerWheelsButton;
    } else {
        return ui->headUpButton;
    }
}

void Raspbed::resetClicks() {
    numRightClicks = 0;
    numLeftClicks = 0;
    qDebug() << "Reset Clicks";
}

void Raspbed::mouseSelectEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (numRightClicks > 0) {
            numLeftClicks++;
            qDebug() << "Pressed Left Click, R="
                     << QString::number(numRightClicks)
                     << ", L=" << QString::number(numLeftClicks);
        }

        selected = false;
        selectedButton->setStyleSheet("");
        selectedButton = nextButton();
        if(settings.isDarkHighlight()){
            selectedButton->setStyleSheet("border: 3px solid black");
        } else {
            selectedButton->setStyleSheet("border: 3px solid white");
        }
    } else if (event->button() == Qt::RightButton) {
        QTimer::singleShot(500, this, SLOT(resetClicks()));
        numRightClicks++;

            if ((numRightClicks >= 2) && (numLeftClicks >= 1)) {
                on_callButton_clicked();
            }

            if (bed.getSerialPort()->isConnected() && selected) {
                if (selectedButton == ui->headUpButton) { // Set correct button
                    headUpHoldButton();
                } else if (selectedButton == ui->headDownButton) {
                    headDownHoldButton();
                } else if (selectedButton == ui->feetUpButton) {
                    feetUpHoldButton();
                } else if (selectedButton == ui->feetDownButton) {
                    feetDownHoldButton();
                } else if (selectedButton == ui->trendButton) {
                    trendHoldButton();
                } else if (selectedButton == ui->bedUpButton) {
                    bedUpHoldButton();
                } else if (selectedButton == ui->bedDownButton) {
                    bedDownHoldButton();
                } else if (selectedButton == ui->lowerWheelsButton) {
                    lowerWheelsHoldButton();
                } else {
                    qDebug() << "Error, button doesn't exist.";
                }
            }

            if(settings.isDarkHighlight()){
                selectedButton->setStyleSheet("background-color: black");
            } else {
                selectedButton->setStyleSheet("background-color: white");
            }

            selected = true;
            qDebug() << "Pressed Right Click, R=" << QString::number(numRightClicks)
                     << ", L=" << QString::number(numLeftClicks);
        }

}

void Raspbed::mousePressEvent(QMouseEvent *event) {
    if (!settings.isButtonMode()) {
        mouseSelectEvent(event);
    }
}

bool Raspbed::eventFilter(QObject *object, QEvent *event) {
    if (!settings.isButtonMode()) {
        if ((event->type() == QEvent::MouseButtonPress)) {
            mouseSelectEvent(static_cast<QMouseEvent *>(event));
            return true;
        }
    }
    return QWidget::eventFilter(object, event);
}

void Raspbed::resetBed() {
    qDebug() << "Stopping serialport to change settings";
    bed.getSerialPort()->stop();
    bed.getSerialPort()->setPortName(settings.getPort().toStdString());
    qDebug() << "Reopening port with " << settings.getPort();
    if (!bed.getSerialPort()->open()) {
        setupButtons();
        QString errorMessage =
            "WARNING: No serial port open. Failure opening " +
            settings.getPort();
        ui->statusBar->showMessage(errorMessage);
    }
}

void Raspbed::setupDisplay() {

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

    if (!settings.isButtonMode()) {
        selectedButton = ui->headUpButton;
        if(settings.isDarkHighlight()){
            selectedButton->setStyleSheet("border: 3px solid black");
        } else {
            selectedButton->setStyleSheet("border: 3px solid white");
        }
    }
}

void Raspbed::setupButtons() {
    QList<QPushButton *> allPButtons =
        ui->centralWidget->findChildren<QPushButton *>();

    for (auto button : allPButtons) {
        button->setIconSize(headUpPixmap.rect().size());
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        if (!bed.getSerialPort()->isConnected()) {
            if (!settings.isButtonMode()) { // Buttons disabled, disable skype
                button->setEnabled(false);
                button->installEventFilter(this);
            } else { // Buttons Enabled, leave skype enabled
                button->setStyleSheet("");
                if (button != ui->callButton) {
                    button->setEnabled(false);
                } else {
                    button->setEnabled(true);
                }
            }
            ui->statusBar->showMessage("WARNING: No serial port detected.");
        } else {
            if (!settings.isButtonMode()) { // Buttons disabled
                button->setEnabled(false);
                button->installEventFilter(this);
            } else {
                button->setStyleSheet("");
                button->setEnabled(true);
            }
            ui->statusBar->showMessage("Connected to port.");
        }
    }
}

void Raspbed::setupIconBorders() {
    if (settings.isBordered()) {
        headUpPixmap = QPixmap(":/icons/border/headUp.png");
        headDownPixmap = QPixmap(":/icons/border/headDown.png");
        feetUpPixmap = QPixmap(":/icons/border/feetUp.png");
        feetDownPixmap = QPixmap(":/icons/border/feetDown.png");
        trendPixmap = QPixmap(":/icons/border/trend.png");
        bedUpPixmap = QPixmap(":/icons/border/bedUp.png");
        bedDownPixmap = QPixmap(":/icons/border/bedDown.png");
        lowerWheelsPixmap = QPixmap(":/icons/border/lowerWheels.png");
        flattenBedPixmap = QPixmap(":/icons/border/flatten.png");
        callPixmap = QPixmap(":/icons/border/call.png");
    } else {
        headUpPixmap = QPixmap(":/icons/no-border/headUp.png");
        headDownPixmap = QPixmap(":/icons/no-border/headDown.png");
        feetUpPixmap = QPixmap(":/icons/no-border/feetUp.png");
        feetDownPixmap = QPixmap(":/icons/no-border/feetDown.png");
        trendPixmap = QPixmap(":/icons/no-border/trend.png");
        bedUpPixmap = QPixmap(":/icons/no-border/bedUp.png");
        bedDownPixmap = QPixmap(":/icons/no-border/bedDown.png");
        lowerWheelsPixmap = QPixmap(":/icons/no-border/lowerWheels.png");
        flattenBedPixmap = QPixmap(":/icons/no-border/flatten.png");
        callPixmap = QPixmap(":/icons/no-border/call.png");
    }
}

/* ******************* Slots ********************/

/**
 * @brief Raspbed::openSettings
 */
void Raspbed::openSettings() {
    std::unique_ptr<Settings> settingsDialog(new Settings);

    QStringList serialPortOptions;
    for (std::string device : bed.getSerialPort()->getDevices()) {
        qDebug() << "Serial option: " << QString::fromStdString(device);
        serialPortOptions.push_back(QString::fromStdString(device));
    }

    settingsDialog->setSerialPorts(serialPortOptions);
    settingsDialog->setPort(settings.getPort());
    settingsDialog->setContact(settings.getContact());
    settingsDialog->setBordered(settings.isBordered());
    settingsDialog->setButtonMode(settings.isButtonMode());
    settingsDialog->setDarkHighlight(settings.isDarkHighlight());
    settingsDialog->setButtonHoldTime(
        QString::number(settings.getButtonHoldTime()));
    settingsDialog->populateSettings();
    settingsDialog->exec();

    if (settingsDialog->result() == QDialog::Accepted) {
        settings.setContact(settingsDialog->getContact());
        settings.setPort(settingsDialog->getPort());
        settings.setBordered(settingsDialog->isBordered());
        settings.setDarkHighlight(settingsDialog->isDarkHighlight());
        settings.setButtonMode(settingsDialog->isButtonMode());
        settings.setButtonHoldTime(settingsDialog->getButtonHoldTime().toInt());
        settings.saveSettings();

        setupDisplay();

        resetBed();
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

void Raspbed::headDownHoldButton() {
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

void Raspbed::headUpHoldButton() {
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

void Raspbed::feetUpHoldButton() {
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

void Raspbed::feetDownHoldButton() {
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

void Raspbed::trendHoldButton() {
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

void Raspbed::bedUpHoldButton() {
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

void Raspbed::bedDownHoldButton() {
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

void Raspbed::lowerWheelsHoldButton() {
    bed.command(bed.relay.lower_wheels, true);
    bed.command(bed.relay.bed_down, true);
    sleep(settings.getButtonHoldTime());
    bed.command(bed.relay.lower_wheels, false);
    bed.command(bed.relay.bed_down, false);
}

void Raspbed::on_flattenBedButton_clicked() {
    ui->statusBar->showMessage("Flattening bed", 20000);
    bed.command(bed.relay.head_down, true);
    bed.command(bed.relay.feet_down, true);
    sleep(20);
    bed.command(bed.relay.head_down, false);
    bed.command(bed.relay.feet_down, false);
}

void Raspbed::on_callButton_clicked() {
    qDebug() << "Calling " << settings.getContact();
    QString message = "Calling skype contact " + settings.getContact();

    ui->statusBar->showMessage(message, 10000);

    std::string skypeCommand =
        "skype --callto " + settings.getContact().toStdString() + " &";

    qDebug() << "skype --callto " + settings.getContact() + " &";

    callInProgress = true;
    system(skypeCommand.c_str());
}

