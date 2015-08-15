/* 
 * File:   SerialPort.cpp
 * Author: john
 * 
 * Created on August 13, 2015, 11:11 PM
 */

#include "SerialPort.hpp"

using namespace std;
using namespace boost::asio;

SerialPort::SerialPort(string name){
    if(portExists(name)){
        port = serial_port_ptr(new serial_port(io));
    }
    
}

// SerialPort::SerialPort(const SerialPort& orig) {}

SerialPort::~SerialPort() {
}

bool SerialPort::portExists(string port){
   DIR *directory = nullptr;
    struct dirent *entry = nullptr; // directory entry
    vector<string> devices;            // List of devices
    
    // The directory /sys/class/tty contains all serial devices
    string portPath = "/sys/class/tty";
     cout << "Opening directory: " << portPath << endl;
    directory = opendir(portPath.c_str());

    // Make sure directory initialized
    if(directory == nullptr){
        cout << "ERROR! pdir could not be initialised correctly" << endl;
        exit(EXIT_FAILURE);
    }
    
    // Get all devices in "/sys/class/tty"
    while (entry = readdir(directory))  {
        // Make sure directory initialized
        if(directory == nullptr){
            cout << "ERROR! pdir could not be initialised correctly" << endl;
            exit(EXIT_FAILURE);
        } else {
            devices.push_back(entry->d_name);
        }
    }
    
    string deviceDriverPath;
    for(auto device : devices){
        deviceDriverPath = portPath + "/" + device + "/device/driver";
        //cout << "\nChecking for match at " << deviceDriverPath << endl;
        
        // Check for active devices
        DIR *driverDir = opendir(deviceDriverPath.c_str());
        if(driverDir && (device == port)){
            cout << "\nMATCH: Serial device '" << device << "' found" << endl;
            closedir(driverDir);
            return true;
        }
    }
    closedir(directory);
    cout << "\nNo match found." << endl;
    return false;
}