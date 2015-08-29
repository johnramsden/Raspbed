/*
 * File:   Bed.cpp
 * Author: John Ramsden
 * Email: ramsdenj@shaw.ca
 *
 * Created on August 18, 2015, 1:30 PM
 */

#include "Bed.hpp"

Bed::Bed() : serialPort(new SerialPort) {
    qDebug() << "Making new bed with serial port values: ";
    serialPort->print();
    serialPort->open();
}

Bed::~Bed() { serialPort->stop(); }

void Bed::Relay::print() {
    qDebug() << "Relays: ";
    qDebug() << "Close all:\t"
             << QString::number(static_cast<unsigned>(close_all));
    qDebug() << "Head up:\t" << QString::number(static_cast<unsigned>(head_up));
    qDebug() << "Head down:\t"
             << QString::number(static_cast<unsigned>(head_down));
    qDebug() << "Feet up:\t" << QString::number(static_cast<unsigned>(feet_up));
    qDebug() << "Feet down:\t"
             << QString::number(static_cast<unsigned>(feet_down));
    qDebug() << "Trend up:\t"
             << QString::number(static_cast<unsigned>(trend_up));
    qDebug() << "Bed up: \t" << QString::number(static_cast<unsigned>(bed_up));
    qDebug() << "Bed down:\t"
             << QString::number(static_cast<unsigned>(bed_down));
    qDebug() << "Set wheels:\t"
             << QString::number(static_cast<unsigned>(lower_wheels));
}

void Bed::command(const char relay, bool on) {
    int val;
    // 1,0,{relay} is on
    if (on) {
        val = 100 + relay;
    } else {
        val = 110 + relay;
    }
    char values[1];
    values[0] = static_cast<char>(val);
    serialPort->write(values);
}

std::shared_ptr<SerialPort> Bed::getSerialPort() { return serialPort; }
