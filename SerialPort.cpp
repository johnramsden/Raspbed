/* 
 * File:   SerialPort.cpp
 * Author: John Ramsden
 * 
 * Created on August 13, 2015, 11:11 PM
 */

#include "SerialPort.hpp"

using namespace boost::asio;

// Default Constructor calls workhorse constructor
SerialPort::SerialPort(std::string name)
    : SerialPort::SerialPort(name, 
            serial_port_base::baud_rate(19200),
            serial_port_base::character_size(8),
            serial_port_base::stop_bits(serial_port_base::stop_bits::two),
            serial_port_base::parity(serial_port_base::parity::none),
            serial_port_base::flow_control(serial_port_base::flow_control::none)) {}


    SerialPort::SerialPort(std::string name,
                serial_port_base::baud_rate baud_rate,
                serial_port_base::character_size character_size,
                serial_port_base::stop_bits stop_bits,
                serial_port_base::parity com_parity,
                serial_port_base::flow_control flow_control) : portName(name),
                                                               baudRate(baud_rate),
                                                               characterSize(character_size),
                                                               stopBits(stop_bits),
                                                               parity(com_parity),
                                                               flowControl(flow_control) {}
    
bool SerialPort::start() {
//    if (port) {
//        std::cout << "error : port is already opened..." << std::endl;
//        return false;
//    }
//    if(portExists(portName)){
//        port = serial_port_ptr(new serial_port(io));
//        std::cout << "\nConnecting to " << portName << std::endl;
//        boost::system::error_code ec;
//        
//        std::string fullName = "/dev/" + portName;
//        
//        port->open(fullName.c_str(), ec);
//        
//        setOptions();
//        
//        if (ec) {
//            std::cout << "\nerror : port_->open() failed...com_port_name="
//                    << portName << ", e=" << ec.message() << std::endl;
//            return false;
//        }
//        return true;
//    } else {
//        std::cout << "error : port doesn't exist..." << std::endl;
//        return false;
//    }
    return true;
}

void SerialPort::stop() {
    if (port) {
        port->cancel();
        port->close();
    }
    io.stop();
    io.reset();
    std::cout << "\nPort closed." << std::endl;
}

void SerialPort::write(const char *data, std::size_t size){
    boost::asio::write(*port, boost::asio::buffer(data, size));
}

void SerialPort::setOptions(){
    // option settings...
    port->set_option(baudRate);
    port->set_option(characterSize);
    port->set_option(stopBits);
    port->set_option(parity);
    port->set_option(flowControl);
    std::cout << "Options set" << std::endl;
}

void SerialPort::print(){
    std::cout << "\nPort: " << getPortName() << std::endl;
    std::cout << "Baud rate: " << getBaudRate().value() << std::endl;
    std::cout << "Character size: " << getCharacterSize().value() << std::endl;
    std::cout << "Flow control: " << getFlowControl().value() << std::endl;
    std::cout << "Parity: " << getParity().value() << std::endl;
    std::cout << "Stop bits: " << getStopBits().value() << std::endl;
}

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

void SerialPort::setPortName(std::string portName) {
    this->portName = portName;
}

std::string SerialPort::getPortName() const {
    return portName;
}