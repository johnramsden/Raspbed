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
    //SerialPort();
    SerialPort(std::string name);
    // SerialPort(const SerialPort& orig);
    virtual ~SerialPort();
    bool portExists(std::string port);
private:
    boost::asio::io_service io;
    serial_port_ptr port;
    std::string com_port;
//    boost::asio::serial_port_base::baud_rate baud_rate;
//    boost::asio::serial_port_base::character_size character_size;
//    boost::asio::serial_port_base::stop_bits stop_bits;
//    boost::asio::serial_port_base::parity parity;
//    boost::asio::serial_port_base::flow_control flow_control;
};

#endif	/* SERIALPORT_HPP */

