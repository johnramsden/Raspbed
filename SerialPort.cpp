/* 
 * File:   SerialPort.cpp
 * Author: john
 * 
 * Created on August 13, 2015, 11:11 PM
 */

#include "SerialPort.hpp"

using namespace boost::asio;

SerialPort::SerialPort(std::string name) : com_port(name) {}

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