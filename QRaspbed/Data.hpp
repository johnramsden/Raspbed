#ifndef DATA_HPP
#define DATA_HPP

#include <QString>
#include <string>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
class Data {

public:
   Data();

   static void loadSettings();
   static void saveSettings();
   static QString getContact();
   static void setContact(const QString &value);

   static bool isBordered();
   static void setBordered(bool value);

   static QString getPort();
   static void setPort(const QString &value);

private:
   Data(Data const&) = delete;
   Data& operator=(Data const&) = delete;

   // Instance variables
   static QString contact;
   static bool iconBorders;
   static QString port;
   static QSettings settings;
};


#endif // DATA_HPP
