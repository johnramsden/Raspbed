#include "Settings.hpp"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateData()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::populateSettings(){
    ui->iconStyleCheckBox->setChecked(bordered);
    ui->callContactLineEdit->setText(contact);
    ui->serialPortComboBox->addItems(serialPorts);
    if(serialPorts.contains(port)){
        ui->serialPortComboBox->setCurrentText(port);
    }
}

void Settings::setSerialPorts(QStringList serialPorts){
    this->serialPorts = serialPorts;
}

QStringList Settings::getSerialPorts(){
    return serialPorts;
}

void Settings::updateData(){
    bordered = ui->iconStyleCheckBox->isChecked();
    contact = ui->callContactLineEdit->text();
    port = ui->serialPortComboBox->itemText(ui->serialPortComboBox->currentIndex());
    qDebug() << "Settings results: Port " << port << ", Contact: " << contact << ", Icon" << bordered;
}

void Settings::setPort(const QString &value)
{
    port = value;
}

QString Settings::getPort(){
    return port;
}
QString Settings::getContact()
{
    return contact;
}

bool Settings::isBordered()
{
    return bordered;
}

void Settings::setBordered(bool value)
{
    bordered = value;
}

void Settings::setContact(const QString &value)
{
    contact = value;
}


