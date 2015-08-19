#include "Raspbed.hpp"
#include "ui_raspbed.h"
#include "SerialPort.hpp"
#include "Bed.hpp"

Raspbed::Raspbed(QWidget *parent) : QMainWindow(parent), ui(new Ui::Raspbed), bed() {
    ui->setupUi(this);
}

Raspbed::~Raspbed() { delete ui; }

//void Raspbed::on_headUpButton_clicked()
//{
//    bed.command(bed.relay.head_down, true);
//    sleep(2);
//    bed.command(bed.relay.head_down, false);
//}

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
