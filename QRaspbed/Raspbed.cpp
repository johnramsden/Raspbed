#include "Raspbed.hpp"
#include "ui_raspbed.h"
#include "SerialPort.hpp"
#include "Bed.hpp"

Raspbed::Raspbed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Raspbed)
{
    ui->setupUi(this);
}

Raspbed::~Raspbed()
{
    delete ui;
}

void Raspbed::on_headDownButton_pressed()
{
    bed.serialPort.write(bed.relay.head_down,true);
}

void Raspbed::on_headDownButton_released()
{
    bed.serialPort.write(bed.relay.head_down,false);
}

void Raspbed::on_headUpButton_pressed()
{

}

void Raspbed::on_headUpButton_released()
{

}

void Raspbed::on_feetUpButton_pressed()
{

}

void Raspbed::on_feetUpButton_released()
{

}


void Raspbed::on_feetDownButton_pressed()
{

}

void Raspbed::on_feetDownButton_released()
{

}

void Raspbed::on_trendButton_pressed()
{

}

void Raspbed::on_trendButton_released()
{

}

void Raspbed::on_bedUpButton_pressed()
{

}

void Raspbed::on_bedUpButton_released()
{

}

void Raspbed::on_bedDownButton_pressed()
{

}

void Raspbed::on_bedDownButton_released()
{

}

void Raspbed::on_lowerWheelsButton_pressed()
{

}

void Raspbed::on_lowerWheelsButton_released()
{

}
