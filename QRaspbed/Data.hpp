#ifndef DATA_HPP
#define DATA_HPP

#include <QString>
#include <string>

class Data {

public:
   Data();

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
};


#endif // DATA_HPP
