/*
 * File:   Bed.cpp
 * Author: John Ramsden
 * Email: ramsdenj@shaw.ca
 *
 * Created on August 18, 2015, 1:30 PM
 */

#include "Bed.hpp"

Bed::Bed() : serialPort(new SerialPort) {
    std::cout << "Making new bed with serial port values: " << std::endl;
    serialPort->print();
    serialPort->open();
}

Bed::Bed(const Bed &orig) {}

Bed::~Bed() {
    serialPort->stop();
}

void Bed::Relay::print() {
    std::cout << "Relays: " << std::endl;
    std::cout << "Close all:\t" << static_cast<unsigned>(close_all)
              << std::endl;
    std::cout << "Head up:\t" << static_cast<unsigned>(head_up) << std::endl;
    std::cout << "Head down:\t" << static_cast<unsigned>(head_down)
              << std::endl;
    std::cout << "Feet up:\t" << static_cast<unsigned>(feet_up) << std::endl;
    std::cout << "Feet down:\t" << static_cast<unsigned>(feet_down)
              << std::endl;
    std::cout << "Trend up:\t" << static_cast<unsigned>(trend_up) << std::endl;
    std::cout << "Bed up: \t" << static_cast<unsigned>(bed_up) << std::endl;
    std::cout << "Bed down:\t" << static_cast<unsigned>(bed_down) << std::endl;
    std::cout << "Set wheels:\t" << static_cast<unsigned>(lower_wheels)
              << std::endl;
}

void Bed::command(const char relay, bool on) {
    std::cout << "Sending " << relay << " to serial port" << std::endl;
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
