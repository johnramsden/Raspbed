/**
 * @file Raspbed.hpp
 * @author John Ramsden
 */

#ifndef RASPBED_HPP
#define RASPBED_HPP

#include "ui_raspbed.h"
#include "Settings.hpp"
#include "SerialPort.hpp"
#include "Bed.hpp"
#include <string>
#include "Data.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

namespace Ui {
class Raspbed;
}

/**
 * @brief The Raspbed class. Holds Main window gui logic.
 */
class Raspbed : public QMainWindow {
    Q_OBJECT

  public:
    /**
     * @brief Raspbed constructor. Loads settings from a Data object,
     * set's up display, and settingsmenu.
     * @param parent
     */
    explicit Raspbed(QWidget *parent = 0);
    ~Raspbed();

private slots:
    /**
     * @brief Slot called upon press of head up button.
     *        Causes a call to write the signal to the relay to raise
     *        head of bed.
     */
    void on_headUpButton_pressed();
    /**
     * @brief Slot called upon release of head down button.
     *        Causes a call to write a signal to the relay to
     *        stop the raising of the head of the bed.
     */
    void on_headUpButton_released();
    /**
     * @brief Slot called upon press of head down button.
     *        Causes a call to write the signal to the relay to lower
     *        the head of bed.
     */
    void on_headDownButton_pressed();
    /**
     * @brief Slot called upon release of head down button.
     *        Causes a call to write a signal to the relay to
     *        stop the lowering of the head of the bed.
     */
    void on_headDownButton_released();
    /**
     * @brief Slot called upon press of feet up button.
     *        Causes a call to write the signal to the relay to raise
     *        the feet of bed.
     */
    void on_feetUpButton_pressed();
    /**
     * @brief Slot called upon release of feet up button.
     *        Causes a call to write a signal to the relay to
     *        stop the raising of the feet of the bed.
     */
    void on_feetUpButton_released();
    /**
     * @brief Slot called upon press of feet down button.
     *        Causes a call to write the signal to the relay
     *        to lower the feet of the bed.
     */
    void on_feetDownButton_pressed();
    /**
     * @brief Slot called upon release of feet down button.
     *        Causes a call to write a signal to the relay to
     *        stop the lowering of the feet of the bed.
     */
    void on_feetDownButton_released();
    /**
     * @brief Slot called upon press of the trend button.
     *        Causes a call to write the signal to the relay to
     *        trend the bed.
     */
    void on_trendButton_pressed();
    /**
     * @brief Slot called upon release of trend button.
     *        Causes a call to write a signal to the relay to
     *        stop the trending of the bed.
     */
    void on_trendButton_released();
    /**
     * @brief Slot called upon press of bed up button.
     *        Causes a call to write the signal to the relay to raise
     *        the bed.
     */
    void on_bedUpButton_pressed();
    /**
     * @brief Slot called upon release of bed up button.
     *        Causes a call to write a signal to the relay to
     *        stop the raising of the bed.
     */
    void on_bedUpButton_released();
    /**
     * @brief Slot called upon press of bed down button.
     *        Causes a call to write the signal to the relay to
     *        lower the bed.
     */
    void on_bedDownButton_pressed();
    /**
     * @brief Slot called upon release of bed down button.
     *        Causes a call to write a signal to the relay to
     *        stop the lowering of the bed.
     */
    void on_bedDownButton_released();
    /**
     * @brief Slot called upon press of the lower wheels button.
     *        Causes a call to write the signal to the relay to
     *        lower the bed and press the wheels button at the same time.
     */
    void on_lowerWheelsButton_pressed();
    /**
     * @brief Slot called upon release of lower wheels button.
     *        Causes a call to write a signal to the relay to
     *        stop the lowering the bed and pressing the wheels button
     *        at the same time.
     */
    void on_lowerWheelsButton_released();
    /**
     * @brief Slot called upon pressing the flatten bed button. It writes
     *        writes a signal to the relay to lower the feet and bed for 20
     *        seconds, then writes a signal to close the relays.
     */
    void on_flattenBedButton_clicked();

    /**
     * @brief Slot called upon press of call button. Sends a command to skype
     *        to call designated skype contact.
     */
    void on_callButton_clicked();

    /**
     * @brief Slot called on press of settings button. Opens a settings dialog.
     * Loops thru all serial port devices and adds them to a list.Loads the different
     * settings variables from the settings class and sets them into the dialog.
     * If the dialog is accepted the settings are saved into the settings class
     * and the display and bed are reloaded.
     */
    void openSettings();

    /**
     * @brief resetClicks Resets numRightClicks and numLeftClicks to 0
     */
    void resetClicks();

  private:
    /**
     * @brief callContact calls your contact using skype
     * @param contact number you want to call in format +6041234567
     */
    void callContact(std::string contact);
    /**
     * @brief setupDisplay sets up the icons by loading the pixmaps into the icons
     * sets them to enabled or disabled depending on settings and sets the styling
     * depending on button mode.
     */
    void setupDisplay();
    /**
     * @brief setupIconBorders sets the icons images to bordered or nonbordered
     * depending on settings.
     */
    void setupIconBorders();
    /**
     * @brief setupButtons sets up the icons size and other settings weather or not
     * they are enabled as well as setting the proper event filter depending on the button mode.
     *
     */
    void setupButtons();
    /**
     * @brief resetBed stops the serial port and resets the port to current port from settings
     */
    void resetBed();

    /**
     * @brief Static settings class containing all of our settings variables.
     */
    Data settings;
    /**
     * @brief settingsMenu menu bar button on tool bar
     */
    QMenu *settingsMenu;
    /**
     * @brief settingsAction is our signal that is triggered upon selecting settings in the tool bar
     * menu.
     */
    QAction *settingsAction;

    /**
     * @brief object pointing to our user interface
     */
    Ui::Raspbed *ui;
    /**
     * @brief Class containing bed specific variables and commands.
     */
    Bed bed;

    // Bed Icons
    /**
     * @brief headUpPixmap head up icon
     */
    QPixmap headUpPixmap;
    /**
     * @brief headDownPixmap head down icon
     */
    QPixmap headDownPixmap;
    /**
     * @brief feetUpPixmap feet up icon
     */
    QPixmap feetUpPixmap;
    /**
     * @brief feetDownPixmap feet down icon
     */
    QPixmap feetDownPixmap;
    /**
     * @brief trendPixmap trend icon
     */
    QPixmap trendPixmap;
    /**
     * @brief bedUpPixmap bed up icon
     */
    QPixmap bedUpPixmap;
    /**
     * @brief bedDownPixmap bed down icon
     */
    QPixmap bedDownPixmap;
    /**
     * @brief lowerWheelsPixmap lower wheels icon
     */
    QPixmap lowerWheelsPixmap;
    /**
     * @brief flattenBedPixmap flatten bed icon
     */
    QPixmap flattenBedPixmap;
    /**
     * @brief callPixmap call bell icon
     */
    QPixmap callPixmap;
    /**
     * @brief selectedButton is the currently selected button when in sip'n puff mode
     */
    QPushButton *selectedButton;
    /**
     * @brief selected is true when a button is selected
     */
    bool selected;
    /**
     * @brief callMade is true if a skype call is in progress
     */
    bool callInProgress;
    /**
     * @brief nextButton finds the next button selected when in sip'n puff mode
     * @return A QPushButton pointer to the next button.
     */
    QPushButton *nextButton();

    /**
     * @brief Event filter for buttons. Only applied if not in button mode.
     * @param object pointer to the object on which the event occur.
     * @param event pointer to the event.
     * @return A boolean value of true if we reenterpreted the event, else we return
     * QWidget::eventFilter(object, event);
     */
    bool eventFilter(QObject *object, QEvent *event);

    /**
     * Common method called for button and window events when not in buttonmode.
     * @brief Raspbed::mouseEvent
     * @param event
     */
    void mouseSelectEvent(QMouseEvent *event);

    /**
     * @brief number of right clicks that have occured since last time clicks were reset
     */
    int numRightClicks;
    /**
     * @brief number of left clicks that have occured since last time clicks were reset
     */
    int numLeftClicks;

    // Held down button clicks for non button mode
    /**
     * @brief command to hold down lower wheels button for the amount of time set in settings
     */
    void lowerWheelsHoldButton();
    /**
     * @brief command to hold down bed down button for the amount of time set in settings
     */
    void bedDownHoldButton();
    /**
     * @brief command to hold down bed up button for the amount of time set in settings
     */
    void bedUpHoldButton();
    /**
     * @brief command to hold down trend button for the amount of time set in settings
     */
    void trendHoldButton();
    /**
     * @brief command to hold down feet down button for the amount of time set in settings
     */
    void feetDownHoldButton();
    /**
     * @brief command to hold down feet up button for the amount of time set in settings
     */
    void feetUpHoldButton();
    /**
     * @brief command to hold down head up button for the amount of time set in settings
     */
    void headUpHoldButton();
    /**
     * @brief command to hold down head down button for the amount of time set in settings
     */
    void headDownHoldButton();

  protected:
    /**
     * @brief Event filter for window. Only applied if not in button mode
     * @param event pointer to the event.
     */
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // RASPBED_HPP
