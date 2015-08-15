/* 
 * File:   SerialPort.cpp
 * Author: john
 * 
 * Created on August 13, 2015, 11:11 PM
 */

#include "SerialPort.hpp"

using namespace std;

SerialPort::SerialPort() {
}

SerialPort::SerialPort(const SerialPort& orig) {
}

SerialPort::~SerialPort() {
}

bool SerialPort::portExists(string port){
   DIR *directory = nullptr;
    struct dirent *entry = nullptr; // directory entry
    vector<string> devices;            // List of devices
    bool portFound = false;           // Return value
    
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
            cout << "Entry: " ;
            cout << entry->d_name << endl;
            devices.push_back(entry->d_name);
        }
    }
    
    struct stat *buf;
    string devicepath;
    for(auto device : devices){
        cout << "Checking device " << device <<  ": ";
        devicepath = portPath + "/" + device;
        
        // Check for active devices
        if(lstat(devicepath.c_str(), buf) == 0){
            cout << "ACTIVE" << endl;
            if(port == devicepath){
                portFound = true;
            }
        } else {
            cout << "INACTIVE" << endl;
            portFound = false;
        }
    }
    
    // Close the directory
    closedir (directory);
    return portFound;
}