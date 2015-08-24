#ifndef RASPBED_HPP
#define RASPBED_HPP

#include "ui_raspbed.h"
#include "Settings.hpp"
#include "SerialPort.hpp"
#include "Bed.hpp"
#include <string>
#include "Data.hpp"
#include <QDebug>

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
private:
    void setupSettings();
    void setupDisplay();
    void setupIconBorders();

    Data settings;
    QMenu* settingsMenu;
    QAction* settingsAction;

    Bed bed;
    Ui::Raspbed* ui;

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
};

#endif // RASPBED_HPP
