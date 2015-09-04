#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QDialog>
#include "Data.hpp"
#include <QDebug>
#include <iostream>

namespace Ui {
class Settings;
}

/**
 * @brief The Settings class contains the logic for the settings dialog.
 */
class Settings : public QDialog {
    Q_OBJECT

  public:
    /**
     * @brief Settings constructor contains the signal and slot connection
     * used to save the data in different fields
     * @param The parent widget.
     */
    explicit Settings(QWidget *parent = 0);

    ~Settings();

    /* ************ Member functions ************ */

    /**
     * @brief Populates the different fields by pulling data out of the QSettings object.
     */
    void populateSettings();

    /* ************ Setters and getters ************ */
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
    bool isDarkHighlight() const;
    void setDarkHighlight(bool value);

private slots:
    /**
     * @brief The slot that is called when the ok button is pressed to save the data in
     * the different fields of the dialog.
     */
    void updateData();

private:
    /* ************ Member variables ************ */
    Ui::Settings *ui;
    /**
     * @brief The list of available serial ports.
     */
    QStringList serialPorts;
    /**
     * @brief Skype contact.
     */
    QString contact;
    /**
     * @brief Selected serial port.
     */
    QString port;
    /**
     * @brief Amount of time to hold a command when in sip'n puff mode.
     */
    QString buttonHoldTime;
    /**
     * @brief When true button icons have a border.
     */
    bool bordered;
    /**
     * @brief When true buttons are pressable.
     */
    bool buttonMode;
    /**
     * @brief When true and in sip'n puff mode the buttons are highlighted in black,
     * when false the buttons are highlighted white.
     */
    bool darkHighlight;
};

#endif // SETTINGS_HPP
