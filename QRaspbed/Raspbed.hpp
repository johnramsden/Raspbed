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

class Raspbed : public QMainWindow {
    Q_OBJECT

  public:
    explicit Raspbed(QWidget *parent = 0);
    ~Raspbed();

  private slots:
    void on_headDownButton_pressed();

    void on_headUpButton_pressed();

    void on_headUpButton_released();

    void on_headDownButton_released();

    void on_feetUpButton_pressed();

    void on_feetUpButton_released();

    void on_feetDownButton_pressed();

    void on_feetDownButton_released();

    void on_trendButton_pressed();

    void on_trendButton_released();

    void on_bedUpButton_pressed();

    void on_bedUpButton_released();

    void on_bedDownButton_pressed();

    void on_bedDownButton_released();

    void on_lowerWheelsButton_pressed();

    void on_lowerWheelsButton_released();

    void on_flattenBedButton_clicked();

    void on_callButton_clicked();

    void openSettings();

    void resetClicks();

  private:
    void setupSettings();
    void setupDisplay();
    void setupIconBorders();
    void setupButtons();
    void resetBed();

    Data settings;
    QMenu *settingsMenu;
    QAction *settingsAction;

    Ui::Raspbed *ui;
    Bed bed;

    // Bed Icons
    QPixmap headUpPixmap;
    QPixmap headDownPixmap;
    QPixmap feetUpPixmap;
    QPixmap feetDownPixmap;
    QPixmap trendPixmap;
    QPixmap bedUpPixmap;
    QPixmap bedDownPixmap;
    QPixmap lowerWheelsPixmap;
    QPixmap flattenBedPixmap;
    QPixmap callPixmap;

    QPushButton *selectedButton;
    bool selected;
    QPushButton *nextButton();

    // Event filtering
    bool eventFilter(QObject *object, QEvent *event);
    void mouseSelectEvent(QMouseEvent *event);

    int numRightClicks;
    int numLeftClicks;

    // Held down button clicks for non button mode
    void lowerWheelsHoldButton();
    void bedDownHoldButton();
    void bedUpHoldButton();
    void trendHoldButton();
    void feetDownHoldButton();
    void feetUpHoldButton();
    void headUpHoldButton();
    void headDownHoldButton();

  protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // RASPBED_HPP
