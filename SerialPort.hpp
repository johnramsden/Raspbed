/* 
 * File:   SerialPort.hpp
 * Author: john
 *
 * Created on August 13, 2015, 11:11 PM
 */

#ifndef SERIALPORT_HPP
#define	SERIALPORT_HPP

#include <linux/serial.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <dirent.h>
#include <iostream>
#include <boost/asio.hpp>
#include  <memory> 

typedef std::shared_ptr<boost::asio::serial_port> serial_port_ptr;

class SerialPort {
public:
    // Constructors
    SerialPort(std::string name);
//    SerialPort();
    SerialPort(std::string name,
                boost::asio::serial_port_base::baud_rate baudRate,
                boost::asio::serial_port_base::character_size characterSize,
                boost::asio::serial_port_base::stop_bits stopBits,
                boost::asio::serial_port_base::parity parity,
                boost::asio::serial_port_base::flow_control flowControl);
    virtual ~SerialPort();
    
    // Member functions
    bool start();
    void print();
    
    // Getters and Setters
    void setFlowControl(boost::asio::serial_port_base::flow_control flowControl);
    boost::asio::serial_port_base::flow_control getFlowControl() const;
    void setParity(boost::asio::serial_port_base::parity parity);
    boost::asio::serial_port_base::parity getParity() const;
    void setStopBits(boost::asio::serial_port_base::stop_bits stopBits);
    boost::asio::serial_port_base::stop_bits getStopBits() const;
    void setCharacterSize(boost::asio::serial_port_base::character_size characterSize);
    boost::asio::serial_port_base::character_size getCharacterSize() const;
    void setBaudRate(boost::asio::serial_port_base::baud_rate baudRate);
    boost::asio::serial_port_base::baud_rate getBaudRate() const;
    void setPortName(std::string portName);
    std::string getPortName() const;
    
private:
    bool portExists(std::string port);
    
    // Member variables
    boost::asio::io_service io;
    serial_port_ptr port;
    std::string portName;
    
    // Port variables
    boost::asio::serial_port_base::baud_rate baudRate;
    boost::asio::serial_port_base::character_size characterSize;
    boost::asio::serial_port_base::stop_bits stopBits;
    boost::asio::serial_port_base::parity parity;
    boost::asio::serial_port_base::flow_control flowControl;
};

#endif	/* SERIALPORT_HPP */

