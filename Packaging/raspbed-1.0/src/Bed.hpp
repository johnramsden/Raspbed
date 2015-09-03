/*
 * File:   Bed.hpp
 * Author: John Ramsden
 * Email: ramsdenj@shaw.ca
 *
 * Created on August 18, 2015, 1:30 PM
 */

#ifndef BED_HPP
#define BED_HPP

#include <iostream>
#include "SerialPort.hpp"
#include <QDebug>

class Bed {
  public:
    /**
     * @brief Bed
     * Default bed constructor
     */
    Bed();

    virtual ~Bed();

    /**
     * @brief Takes a relay number from 0 to 7 and respose with the byte code
     * to write to serial port. an on or off boolean value is given in
     * order to give the appropriate code to turn the relay on or off.
     * @param relay is a number zero through seven which should be one of the Relay struct variables
     * @param on is a boolean value setting the given relay on or off.
     */
    void command(const char relay, bool on);

    /**
     * @brief getter for serialPort.
     * @return Shared pointer to SerialPort object.
     */
    std::shared_ptr<SerialPort> getSerialPort();
    /**
     * Struct containing the relay values and a print to command.
     * @brief The Relay struct
     */
    struct Relay {
        void print();
        const char close_all = 0;
        const char head_up = 1;
        const char head_down = 2;
        const char feet_up = 3;
        const char feet_down = 4;
        const char trend_up = 5;
        const char bed_up = 6;
        const char bed_down = 7;
        const char lower_wheels = 8;
    } relay;

  private:
    /**
     * @brief serialPort contains all of the serialport logic.
     * @return Shared pointer to SerialPort object.
     */
    std::shared_ptr<SerialPort> serialPort;
};

#endif /* BED_HPP */
