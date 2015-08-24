#include "Data.hpp"

QString Data::contact;
bool Data::iconBorders;
QString Data::port;

Data::Data() {}

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


