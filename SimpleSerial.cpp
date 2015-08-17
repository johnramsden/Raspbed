/* 
 * File:   SimpleSerial.cpp
 * Author: john
 * 
 * Created on August 16, 2015, 10:56 PM
 */

#include "SimpleSerial.hpp"

#include <boost/asio.hpp>


using namespace boost::asio;

// Default Constructor calls workhorse constructor
SimpleSerial::SimpleSerial(std::string name)
    : SimpleSerial::SimpleSerial(
            name, 
            19200,
            serial_port_base::character_size(8),
            serial_port_base::stop_bits(serial_port_base::stop_bits::two),
            serial_port_base::parity(serial_port_base::parity::none),
            serial_port_base::flow_control(serial_port_base::flow_control::none)) {}


SimpleSerial::SimpleSerial(std::string name, unsigned int baud_rate,
        serial_port_base::character_size character_size,
        serial_port_base::stop_bits stop_bits,
        serial_port_base::parity com_parity,
        serial_port_base::flow_control flow_control) 
        : portName(name), baudRate(serial_port_base::baud_rate(baud_rate)),
          characterSize(character_size), stopBits(stop_bits),
          parity(com_parity), flowControl(flow_control), io(), port(io) {
}

SimpleSerial::~SimpleSerial() {
}

bool SimpleSerial::open() {
    if (port.is_open()) {
        std::cout << "Port is already opened, closing..." << std::endl;
        port.close();
    }
    std::string fullName = "/dev/" + portName;
    port.open(fullName);
    
    if (port.is_open()) {
        port.set_option(baudRate);
        port.set_option(characterSize);
        port.set_option(stopBits);
        port.set_option(parity);
        port.set_option(flowControl);
        std::cout << "Options set" << std::endl;

        return false;
    } else {
        std::cout << "error : port isn't open..." << std::endl;
        return true;
    }
}

void SimpleSerial::stop() {
    if (port.is_open()) {
        port.cancel();
        port.close();
    }
    io.stop();
    io.reset();
    std::cout << "\nPort closed." << std::endl;
}

void SimpleSerial::write(const char *data, std::size_t size){
    boost::asio::write(port, boost::asio::buffer(data, size));
}



void SimpleSerial::print(){
//    std::cout << "\nPort: " << getPortName() << std::endl;
//    std::cout << "Baud rate: " << getBaudRate().value() << std::endl;
//    std::cout << "Character size: " << getCharacterSize().value() << std::endl;
//    std::cout << "Flow control: " << getFlowControl().value() << std::endl;
//    std::cout << "Parity: " << getParity().value() << std::endl;
//    std::cout << "Stop bits: " << getStopBits().value() << std::endl;
}

bool SimpleSerial::portExists(std::string port){
   DIR *directory = nullptr;
    struct dirent *entry = nullptr; // directory entry
    std::vector<std::string> devices;            // List of devices
    
    // The directory /sys/class/tty contains all serial devices
    std::string portPath = "/sys/class/tty";
     std::cout << "Opening directory: " << portPath << std::endl;
    directory = opendir(portPath.c_str());

    // Make sure directory initialized
    if(directory == nullptr){
        std::cout << "ERROR! pdir could not be initialised correctly" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Get all devices in "/sys/class/tty"
    while (entry = readdir(directory))  {
        // Make sure directory initialized
        if(directory == nullptr){
            std::cout << "ERROR! pdir could not be initialised correctly" << std::endl;
            exit(EXIT_FAILURE);
        } else {
            devices.push_back(entry->d_name);
        }
    }
    
    std::string deviceDriverPath;
    for(auto device : devices){
        deviceDriverPath = portPath + "/" + device + "/device/driver";
        //std::cout << "\nChecking for match at " << deviceDriverPath << std::endl;
        
        // Check for active devices
        DIR *driverDir = opendir(deviceDriverPath.c_str());
        if(driverDir && (device == port)){
            std::cout << "\nMATCH: Serial device '" << device << "' found" << std::endl;
            closedir(driverDir);
            return true;
        }
    }
    closedir(directory);
    std::cout << "\nNo match found." << std::endl;
    return false;
}

void SimpleSerial::setFlowControl(boost::asio::serial_port_base::flow_control flowControl) {
    this->flowControl = flowControl;
}

boost::asio::serial_port_base::flow_control SimpleSerial::getFlowControl() const {
    return flowControl;
}

void SimpleSerial::setParity(boost::asio::serial_port_base::parity parity) {
    this->parity = parity;
}

boost::asio::serial_port_base::parity SimpleSerial::getParity() const {
    return parity;
}

void SimpleSerial::setStopBits(boost::asio::serial_port_base::stop_bits stopBits) {
    this->stopBits = stopBits;
}

boost::asio::serial_port_base::stop_bits SimpleSerial::getStopBits() const {
    return stopBits;
}

void SimpleSerial::setCharacterSize(boost::asio::serial_port_base::character_size characterSize) {
    this->characterSize = characterSize;
}

boost::asio::serial_port_base::character_size SimpleSerial::getCharacterSize() const {
    return characterSize;
}

void SimpleSerial::setBaudRate(boost::asio::serial_port_base::baud_rate baudRate) {
    this->baudRate = baudRate;
}

boost::asio::serial_port_base::baud_rate SimpleSerial::getBaudRate() const {
    return baudRate;
}

void SimpleSerial::setPortName(std::string portName) {
    this->portName = portName;
}

std::string SimpleSerial::getPortName() const {
    return portName;
}