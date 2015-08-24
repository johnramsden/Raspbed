#include "Settings.hpp"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->iconStyleCheckBox->setChecked(true);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::populateSettings(){
    ui->serialPortComboBox->addItems(serialPorts);
}

void Settings::setSerialPorts(QStringList serialPorts){
    this->serialPorts = serialPorts;
}

QStringList Settings::getSerialPorts(){
    return serialPorts;
}

void Settings::on_buttonBox_accepted()
{
    contact = ui->callContactLineEdit->text();
   // port = ui->serialPortComboBox->itemData(ui->serialPortComboBox->currentIndex());
    bordered = ui->iconStyleCheckBox->isChecked();
}
