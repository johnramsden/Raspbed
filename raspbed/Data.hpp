#ifndef DATA_HPP
#define DATA_HPP

#include <QString>
#include <string>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>

/**
 * @brief The Data class contains all the settings data variables as well as
 * the saving and loading of data that needs to persist between running the application.
 */
class Data {
  public:
    /**
     * @brief Data consructor, sets the organization name and application name for
     * the settings object. On some computers you may need to set permissions in QSettings file
     * in order to make settings persist between runs.
     */
    Data();

    /* ************ Regular functions ************ */
    /**
     * @brief loadSettings loads the settings for the port, icon borders, contact,
     * button mode, button hold time and button highlight color
     */
    static void loadSettings();
    /**
     * @brief saveSettings sets the settings for the port, icon borders, contact,
     * button mode, button hold time and button highlight color
     */
    static void saveSettings();

    /* ************ setters and getters ************ */
    static QString getContact();
    static void setContact(const QString &value);
    static bool isButtonMode();
    static void setButtonMode(bool value);
    static bool isBordered();
    static void setBordered(bool value);
    static QString getPort();
    static void setPort(const QString &value);
    static int getButtonHoldTime();
    static void setButtonHoldTime(int value);
    static bool isDarkHighlight();
    static void setDarkHighlight(bool value);

private:
    Data(Data const &) = delete;
    Data &operator=(Data const &) = delete;

    /* ************ Member variables ************ */
    /**
     * @brief skype contact that is called with emergency button
     */
    static QString contact;
    /**
     * @brief iconBorders when set true turns on the borders on the button icons
     */
    static bool iconBorders;
    /**
     * @brief Name of serial port in the format ttyUSB0
     */
    static QString port;
    /**
     * @brief QSettings object that is used to persist settings between runs, makes Raspbed
     * folder containing settings file.
     */
    static QSettings settings;
    /**
     * @brief When buttonMode is set the buttons are pressable for use with a mouse,
     * ideally for use on desktop. When buttonmode is set off the buttons toggle through
     * on right clicks and select a button with left clicks.
     */
    static bool buttonMode;
    /**
     * @brief The amount of time a command continues for after a button is pressed.
     */
    static int buttonHoldTime;
    /**
     * @brief When set on the buttons are highlighted in black for use with white screen,
     * when off the buttons are highlighted white.
     */
    static bool darkHighlight;
};

#endif // DATA_HPP
