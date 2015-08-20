#include "Raspbed.hpp"
#include "ui_raspbed.h"
#include "SerialPort.hpp"
#include "Bed.hpp"

Raspbed::Raspbed(QWidget *parent) : QMainWindow(parent), ui(new Ui::Raspbed), bed() {
    ui->setupUi(this);

    QPixmap headUpPixmap("images/head-up-icon.jpg");
    QIcon headUpButtonIcon(headUpPixmap);
    ui->headUpButton->setIcon(headUpButtonIcon);
    ui->headUpButton->setIconSize(headUpPixmap.rect().size());
    QSize headUpButtonSize(headUpPixmap.rect().size().width() + 15,
                           headUpPixmap.rect().size().height() + 15);
    ui->headUpButton->setFixedSize(headUpButtonSize);

    QPixmap headDownPixmap("images/head-down-icon.jpg");
    QIcon headDownButtonIcon(headDownPixmap);
    ui->headDownButton->setIcon(headDownButtonIcon);
    ui->headDownButton->setIconSize(headDownPixmap.rect().size());
    QSize headDownButtonSize(headDownPixmap.rect().size().width() + 15,
                           headDownPixmap.rect().size().height() + 15);
    ui->headDownButton->setFixedSize(headDownButtonSize);

    QPixmap feetUpPixmap("images/feet-up-icon.jpg");
    QIcon feetUpButtonIcon(feetUpPixmap);
    ui->feetUpButton->setIcon(feetUpButtonIcon);
    ui->feetUpButton->setIconSize(feetUpPixmap.rect().size());
    QSize feetUpButtonSize(feetUpPixmap.rect().size().width() + 15,
                           feetUpPixmap.rect().size().height() + 15);
    ui->feetUpButton->setFixedSize(feetUpButtonSize);

    QPixmap feetDownPixmap("images/feet-down-icon.jpg");
    QIcon feetDownButtonIcon(feetDownPixmap);
    ui->feetDownButton->setIcon(feetDownButtonIcon);
    ui->feetDownButton->setIconSize(feetDownPixmap.rect().size());
    QSize feetDownButtonSize(feetDownPixmap.rect().size().width() + 15,
                           feetDownPixmap.rect().size().height() + 15);
    ui->feetDownButton->setFixedSize(feetDownButtonSize);

    QPixmap trendPixmap("images/trend-icon.jpg");
    QIcon trendButtonIcon(trendPixmap);
    ui->trendButton->setIcon(trendButtonIcon);
    ui->trendButton->setIconSize(trendPixmap.rect().size());
    QSize trendButtonSize(trendPixmap.rect().size().width() + 15,
                           trendPixmap.rect().size().height() + 15);
    ui->trendButton->setFixedSize(trendButtonSize);

    QPixmap bedUpPixmap("images/bed-up-icon.jpg");
    QIcon bedUpButtonIcon(bedUpPixmap);
    ui->bedUpButton->setIcon(bedUpButtonIcon);
    ui->bedUpButton->setIconSize(bedUpPixmap.rect().size());
    QSize bedUpButtonSize(bedUpPixmap.rect().size().width() + 15,
                           bedUpPixmap.rect().size().height() + 15);
    ui->bedUpButton->setFixedSize(bedUpButtonSize);

    QPixmap bedDownPixmap("images/bed-down-icon.jpg");
    QIcon bedDownButtonIcon(bedDownPixmap);
    ui->bedDownButton->setIcon(bedDownButtonIcon);
    ui->bedDownButton->setIconSize(bedDownPixmap.rect().size());
    QSize bedDownButtonSize(bedDownPixmap.rect().size().width() + 15,
                           bedDownPixmap.rect().size().height() + 15);
    ui->bedDownButton->setFixedSize(bedDownButtonSize);

    QPixmap lowerWheelsPixmap("images/lower-wheels-icon.jpg");
    QIcon lowerWheelsButtonIcon(lowerWheelsPixmap);
    ui->lowerWheelsButton->setIcon(lowerWheelsButtonIcon);
    ui->lowerWheelsButton->setIconSize(lowerWheelsPixmap.rect().size());
    QSize lowerWheelsButtonSize(lowerWheelsPixmap.rect().size().width() + 15,
                           lowerWheelsPixmap.rect().size().height() + 15);
    ui->lowerWheelsButton->setFixedSize(lowerWheelsButtonSize);
}

Raspbed::~Raspbed() { delete ui; }

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
