/* 
 * File:   SerialPort.hpp
 * Author: john
 *
 * Created on August 16, 2015, 10:56 PM
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

class SerialPort {
public:
    // Constructors
    SerialPort(std::string name);
//    SimpleSerial();
    SerialPort(std::string name, unsigned int baud_rate,
        boost::asio::serial_port_base::character_size character_size,
        boost::asio::serial_port_base::stop_bits stop_bits,
        boost::asio::serial_port_base::parity com_parity,
        boost::asio::serial_port_base::flow_control flow_control) ;
    virtual ~SerialPort();
    
    // Member functions
    bool open();
    void stop();
    void write(const char *data, size_t size);
    void print();
    
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
    boost::asio::serial_port port;
    std::string portName;
    
    // Port variables
    boost::asio::serial_port_base::baud_rate baudRate;
    boost::asio::serial_port_base::character_size characterSize;
    boost::asio::serial_port_base::stop_bits stopBits;
    boost::asio::serial_port_base::parity parity;
    boost::asio::serial_port_base::flow_control flowControl;
};

#endif	/* SERIALPORT_HPP */

