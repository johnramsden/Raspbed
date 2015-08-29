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
    ui->buttonModeCheckBox->setChecked(buttonMode);
    ui->callContactLineEdit->setText(contact);
    ui->serialPortComboBox->addItems(serialPorts);
    ui->buttonHoldTimeEdit->setText(buttonHoldTime);
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
    buttonMode = ui->buttonModeCheckBox->isChecked();
    contact = ui->callContactLineEdit->text();
    buttonHoldTime = ui->buttonHoldTimeEdit->text();
    port = ui->serialPortComboBox->itemText(ui->serialPortComboBox->currentIndex());
    qDebug() << "------------------\nSettings results: \nPort "
             << port << "\nContact: " << contact << "\nIcon" << bordered
             << "Button Mode:" << buttonMode;
}

QString Settings::getButtonHoldTime() const
{
    return buttonHoldTime;
}

void Settings::setButtonHoldTime(const QString &value)
{
    buttonHoldTime = value;
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

bool Settings::isButtonMode()
{
    return buttonMode;
}

void Settings::setButtonMode(bool value)
{
    buttonMode = value;
}
