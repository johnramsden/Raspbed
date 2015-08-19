#include "Raspbed.hpp"
#include "ui_raspbed.h"

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
