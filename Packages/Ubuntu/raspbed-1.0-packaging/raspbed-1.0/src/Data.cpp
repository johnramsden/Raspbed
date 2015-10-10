#include "Data.hpp"

QString Data::contact;
bool Data::iconBorders;
bool Data::buttonMode;
QString Data::port;
QSettings Data::settings;
int Data::buttonHoldTime;

Data::Data() {
    QCoreApplication::setOrganizationName("RamsdenJ");
    QCoreApplication::setApplicationName("Raspbed");
}

void Data::loadSettings() {
    qDebug() << "-------------------\nLoading settings:";
    port = settings.value("serialport").toString();
    iconBorders = settings.value("icons").toBool();
    contact = settings.value("contact").toString();
    buttonMode = settings.value("buttonMode").toBool();
    buttonHoldTime = settings.value("buttonHoldTime").toInt();
    qDebug() << "Loaded: \nPort: " << port << "\nIcons:" << iconBorders
             << "\nContact:" << contact << "\nButtons" << buttonMode;
}

void Data::saveSettings() {
    qDebug() << "Saving settings:";
    settings.setValue("serialport", port);
    settings.setValue("icons", iconBorders);
    settings.setValue("contact", contact);
    settings.setValue("buttonMode", buttonMode);
    settings.setValue("buttonHoldTime", buttonHoldTime);
    qDebug() << "Saved: \nPort: " << port << "\nIcons:" << iconBorders
             << "\nContact:" << contact << "Buttons" << buttonMode;
}

QString Data::getContact() { return contact; }

void Data::setContact(const QString &value) { contact = value; }
bool Data::isBordered() { return iconBorders; }

void Data::setBordered(bool value) { iconBorders = value; }
QString Data::getPort() { return port; }

void Data::setPort(const QString &value) { port = value; }

int Data::getButtonHoldTime() { return buttonHoldTime; }

void Data::setButtonHoldTime(int value) { buttonHoldTime = value; }

bool Data::isButtonMode() { return buttonMode; }

void Data::setButtonMode(bool value) { buttonMode = value; }
