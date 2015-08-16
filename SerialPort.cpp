/* 
 * File:   SerialPort.cpp
 * Author: john
 * 
 * Created on August 13, 2015, 11:11 PM
 */

#include "SerialPort.hpp"

using namespace boost::asio;

SerialPort::SerialPort(std::string name) : com_port(name) {}

// Default Constructor calls workhorse constructor
//SerialPort::SerialPort()
//    : SerialPort::SerialPort("ttyUSB0", 
//            boost::asio::serial_port_base::baud_rate(19200),
//            boost::asio::serial_port_base::character_size(8),
//            boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::two),
//            boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none),
//            boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none))
//{}
//
//
//    SerialPort::SerialPort(std::string name,
//                boost::asio::serial_port_base::baud_rate baud_rate,
//                boost::asio::serial_port_base::character_size character_size,
//                boost::asio::serial_port_base::stop_bits stop_bits,
//                boost::asio::serial_port_base::parity com_parity,
//                boost::asio::serial_port_base::flow_control flow_control)
//    
//    : com_port(name),
//      baudRate(baud_rate),
//      characterSize(character_size),
//      stopBits(stop_bits),
//      parity(com_parity),
//      flowControl(flow_control) {}
    

    
	// option settings...
//	port_->set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
//	port_->set_option(boost::asio::serial_port_base::character_size(8));
//	port_->set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
//	port_->set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
//	port_->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

bool SerialPort::connect() {
    if (port) {
        std::cout << "error : port is already opened..." << std::endl;
        return false;
    }
    if(portExists(com_port)){
        port = serial_port_ptr(new serial_port(io));
        std::cout << "Success : connected to " << com_port << std::endl;
        return true;
    } else {
        std::cout << "error : port doesn't exist..." << std::endl;
        return false;
    }
}

void SerialPort::setFlowControl(serial_port_base::flow_control flowControl) {
    this->flowControl = flowControl;
}

serial_port_base::flow_control SerialPort::getFlowControl() const {
    return flowControl;
}

void SerialPort::setParity(serial_port_base::parity parity) {
    this->parity = parity;
}

serial_port_base::parity SerialPort::getParity() const {
    return parity;
}

void SerialPort::setStopBits(serial_port_base::stop_bits stopBits) {
    this->stopBits = stopBits;
}

serial_port_base::stop_bits SerialPort::getStopBits() const {
    return stopBits;
}

void SerialPort::setCharacterSize(serial_port_base::character_size characterSize) {
    this->characterSize = characterSize;
}

serial_port_base::character_size SerialPort::getCharacterSize() const {
    return characterSize;
}

void SerialPort::setBaudRate(serial_port_base::baud_rate baudRate) {
    this->baudRate = baudRate;
}

serial_port_base::baud_rate SerialPort::getBaudRate() const {
    return baudRate;
}

void SerialPort::setCom_port(std::string com_port) {
    this->com_port = com_port;
}

std::string SerialPort::getCom_port() const {
    return com_port;
}

// SerialPort::SerialPort(const SerialPort& orig) {}

SerialPort::~SerialPort() {
}

bool SerialPort::portExists(std::string port){
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