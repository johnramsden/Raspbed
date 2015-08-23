#include "Raspbed.hpp"

Raspbed::Raspbed(QWidget *parent) : QMainWindow(parent), ui(new Ui::Raspbed), bed() {
    ui->setupUi(this);
    setupIcons();
    QFont f( "Arial", 24, QFont::Bold);
    ui->currentStatusLabel->setFont(f);
}

Raspbed::~Raspbed() { delete ui; }

void Raspbed::setupIcons(){

    useIconBorders(true);

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

    QList<QPushButton *> allPButtons = ui->centralWidget->findChildren<QPushButton *>();

    for(auto button : allPButtons){
        button->setIconSize(headUpPixmap.rect().size());
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    }

}

void Raspbed::useIconBorders(bool border){
    if(border){
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
        ui->currentStatusLabel->setText("Lowering head of bed...");
    }
}

void Raspbed::on_headDownButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.head_down, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_headUpButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.head_up, true);
        ui->currentStatusLabel->setText("Raising head of bed...");
    }
}

void Raspbed::on_headUpButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.head_up, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_feetUpButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.feet_up, true);
        ui->currentStatusLabel->setText("Raising foot of bed...");
            }
}

void Raspbed::on_feetUpButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.feet_up, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_feetDownButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.feet_down, true);
        ui->currentStatusLabel->setText("Lowering foot of bed...");
    }
}

void Raspbed::on_feetDownButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.feet_down, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_trendButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.trend_up, true);
        ui->currentStatusLabel->setText("Trending bed...");
    }
}

void Raspbed::on_trendButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.trend_up, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_bedUpButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.bed_up, true);
        ui->currentStatusLabel->setText("Raising bed...");
    }
}

void Raspbed::on_bedUpButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.bed_up, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_bedDownButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.bed_down, true);
        ui->currentStatusLabel->setText("Lowering bed...");
    }
}

void Raspbed::on_bedDownButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.bed_down, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_lowerWheelsButton_pressed() {
    if(bed.getSerialPort()->isConnected()){
    bed.command(bed.relay.lower_wheels, true);
    bed.command(bed.relay.bed_down, true);
    ui->currentStatusLabel->setText("Lowering wheels...");
    }
}

void Raspbed::on_lowerWheelsButton_released() {
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.lower_wheels, false);
        bed.command(bed.relay.bed_down, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_flattenBedButton_clicked(){
    if(bed.getSerialPort()->isConnected()){
        bed.command(bed.relay.head_down, true);
        bed.command(bed.relay.feet_down, true);
        sleep(20);
        bed.command(bed.relay.head_down, false);
        bed.command(bed.relay.feet_down, false);
        ui->currentStatusLabel->setText("");
    }
}

void Raspbed::on_flattenBedButton_pressed()
{
     ui->currentStatusLabel->setText("Flattening bed");
}

void Raspbed::on_callButton_clicked()
{
    system("skype --callto +16049263981 &");
}
