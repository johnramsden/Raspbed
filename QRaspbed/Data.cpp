#include "Data.hpp"

QString Data::contact;
bool Data::iconBorders;
QString Data::port;
QSettings Data::settings;

Data::Data() {
    QCoreApplication::setOrganizationName("RamsdenJ");
    QCoreApplication::setApplicationName("Raspbed");
}

void  Data::loadSettings(){
    qDebug() << "Loading settings:";
    port = settings.value("serialport").toString();
    iconBorders = settings.value("icons").toBool();
    contact = settings.value("contact").toString();
    qDebug() << "Loaded " << port << ", " << iconBorders << ", and " << contact;
}

void  Data::saveSettings(){
    qDebug() << "Saving settings:";
    settings.setValue("serialport", port);
    settings.setValue("icons", iconBorders);
    settings.setValue("contact", contact);
    qDebug() << "Saved " << port << ", " << iconBorders << ", and " << contact;
}

QString Data::getContact()
{
    return contact;
}

void Data::setContact(const QString &value)
{
    contact = value;
}
bool Data::isBordered()
{
    return iconBorders;
}

void Data::setBordered(bool value)
{
    iconBorders = value;
}
QString Data::getPort()
{
    return port;
}

void Data::setPort(const QString &value)
{
    port = value;
}


