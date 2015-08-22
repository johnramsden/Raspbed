#include "Raspbed.hpp"
#include "ui_raspbed.h"
#include "SerialPort.hpp"
#include "Bed.hpp"

Raspbed::Raspbed(QWidget *parent) : QMainWindow(parent), ui(new Ui::Raspbed), bed() {
    ui->setupUi(this);

    setupIcons();
}

Raspbed::~Raspbed() { delete ui; }

void Raspbed::setupIcons(){
    useIconBorders(false);

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
        headUpPixmap =  QPixmap("images/no-border/headDownButton.png");
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
}

void Raspbed::on_headDownButton_released() {
    bed.command(bed.relay.head_down, false);
}

void Raspbed::on_headUpButton_pressed() {
    bed.command(bed.relay.head_up, true);
}

void Raspbed::on_headUpButton_released() {
    bed.command(bed.relay.head_up, false);
}

void Raspbed::on_feetUpButton_pressed() {
    bed.command(bed.relay.feet_up, true);
}

void Raspbed::on_feetUpButton_released() {
    bed.command(bed.relay.feet_up, false);
}

void Raspbed::on_feetDownButton_pressed() {
    bed.command(bed.relay.feet_down, true);
}

void Raspbed::on_feetDownButton_released() {
    bed.command(bed.relay.feet_down, false);
}

void Raspbed::on_trendButton_pressed() {
    bed.command(bed.relay.trend_up, true);
}

void Raspbed::on_trendButton_released() {
    bed.command(bed.relay.trend_up, false);
}

void Raspbed::on_bedUpButton_pressed() {
    bed.command(bed.relay.bed_up, true);
}

void Raspbed::on_bedUpButton_released() {
    bed.command(bed.relay.bed_up, false);
}

void Raspbed::on_bedDownButton_pressed() {
    bed.command(bed.relay.bed_down, true);
}

void Raspbed::on_bedDownButton_released() {
    bed.command(bed.relay.bed_down, false);
}

void Raspbed::on_lowerWheelsButton_pressed() {
    bed.command(bed.relay.lower_wheels, true);
    bed.command(bed.relay.bed_down, true);
}

void Raspbed::on_lowerWheelsButton_released() {
    bed.command(bed.relay.lower_wheels, false);
    bed.command(bed.relay.bed_down, false);
}

void Raspbed::on_flattenBedButton_clicked()
{
    bed.command(bed.relay.head_down, true);
    bed.command(bed.relay.feet_down, true);
    sleep(20);
    bed.command(bed.relay.head_down, false);
    bed.command(bed.relay.feet_down, false);
}
