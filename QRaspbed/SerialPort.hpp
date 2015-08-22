/*
 * File:   SerialPort.hpp
 * Author: John Ramsden
 * Email: ramsdenj@shaw.ca
 *
 * Created on August 18, 2015, 10:56 PM
 */

#ifndef SERIALPORT_HPP
#define SERIALPORT_HPP

#include <linux/serial.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <dirent.h>
#include <iostream>
#include <boost/asio.hpp>
#include <memory>

class SerialPort {
  public:
    // Constructors

    /**
         * Constructor. Default constructor.Creates and opens a serial device.
         * \param name serial device name, example "ttyUSB0"
         */
    SerialPort(std::string name = "ttyUSB0");

    /**
     * Constructor: Main constructor that takes serial port options
         * Creates and opens a serial device.
         * \param devname serial device name, example ttyUSB0"
         * \param baud_rate serial baud rate
         * \param opt_parity serial parity, default none
         * \param opt_csize serial character size, default 8bit
         * \param opt_flow serial flow control, default none
         * \param opt_stop serial stop bits, default 1
         * \throws boost::system::system_error if cannot open the
         * serial device
         */
    SerialPort(std::string name, unsigned int baud_rate,
               boost::asio::serial_port_base::character_size character_size,
               boost::asio::serial_port_base::stop_bits stop_bits,
               boost::asio::serial_port_base::parity com_parity,
               boost::asio::serial_port_base::flow_control flow_control);

    /**
     * Destructor
     */
    virtual ~SerialPort();

    // Member functions

    /**
     * Open serial port, and sets all options.
     * Returns true if port was successfully open
     */
    bool open();

    /**
     * Closes the port
     */
    void stop();

    /**
     * Write data to serial port. Returns immediately.
     * \param data array of char to be sent through the serial device
     * \param size array size
     */
    void write(const char *data);

    /**
     * @brief print
     * Prints all of set options
     */
    void print();

    // setters and getters
    void
    setFlowControl(boost::asio::serial_port_base::flow_control flowControl);
    boost::asio::serial_port_base::flow_control getFlowControl() const;
    void setParity(boost::asio::serial_port_base::parity parity);
    boost::asio::serial_port_base::parity getParity() const;
    void setStopBits(boost::asio::serial_port_base::stop_bits stopBits);
    boost::asio::serial_port_base::stop_bits getStopBits() const;
    void setCharacterSize(
        boost::asio::serial_port_base::character_size characterSize);
    boost::asio::serial_port_base::character_size getCharacterSize() const;
    void setBaudRate(boost::asio::serial_port_base::baud_rate baudRate);
    boost::asio::serial_port_base::baud_rate getBaudRate() const;
    void setPortName(std::string portName);
    std::string getPortName() const;

  private:
    /**
     * @brief portExists
     * @param port Name of port to check for. Given in format "ttyUSB0"
     * @return Returns true if port exists
     */
    bool portExists(std::string port);

    // Member variables
    boost::asio::io_service io;
    boost::asio::serial_port port;
    std::string portName;

    // Port variables
    boost::asio::serial_port_base::baud_rate baudRate;
    boost::asio::serial_port_base::character_size characterSize;
    boost::asio::serial_port_base::stop_bits stopBits;
    boost::asio::serial_port_base::parity parity;
    boost::asio::serial_port_base::flow_control flowControl;
};

#endif /* SERIALPORT_HPP */
