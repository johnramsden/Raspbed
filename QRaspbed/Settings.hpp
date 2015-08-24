#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QDialog>
#include "Data.hpp"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void populateSettings();

    void setSerialPorts(QStringList serialPorts);

    QStringList getSerialPorts();

    QString getContact();

    QString getPort();

    bool isBordered();


    void setContact(const QString &value);

    bool getBordered() const;
    void setBordered(bool value);

    void setPort(const QString &value);

private slots:
    void on_buttonBox_accepted();

private:
    QStringList serialPorts;
    Ui::Settings *ui;

    QString contact;
    bool bordered;
    QString port;
};

#endif // SETTINGS_HPP
