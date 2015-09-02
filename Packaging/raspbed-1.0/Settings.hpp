#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QDialog>
#include "Data.hpp"
#include <QDebug>
#include <iostream>

namespace Ui {
class Settings;
}

class Settings : public QDialog {
    Q_OBJECT

  public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void populateSettings();

    void setSerialPorts(QStringList serialPorts);

    QStringList getSerialPorts();

    void setPort(const QString &value);
    QString getPort();

    void setContact(const QString &value);
    QString getContact();

    bool isBordered();
    void setBordered(bool value);

    bool isButtonMode();
    void setButtonMode(bool value);

    QString getButtonHoldTime() const;
    void setButtonHoldTime(const QString &value);

  private slots:
    void updateData();

  private:
    QStringList serialPorts;
    Ui::Settings *ui;

    QString contact;
    bool bordered;
    bool buttonMode;
    QString port;
    QString buttonHoldTime;
};

#endif // SETTINGS_HPP
