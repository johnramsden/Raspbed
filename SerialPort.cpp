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
            // cout << "Entry: " ;
            // cout << entry->d_name << endl;
            devices.push_back(entry->d_name);
        }
    }
    
    string deviceDriverPath;
    for(auto device : devices){
        deviceDriverPath = portPath + "/" + device + "/device/driver";
        
        cout << "\Checking for match at " << deviceDriverPath << endl;
        
        // Check for active devices
        DIR* driverDir = opendir(deviceDriverPath.c_str());
        if(driverDir && (device == port)){
            cout << "Driver " << device << " match at " << deviceDriverPath << endl;
            closedir(driverDir);
            return true;
        }
    }
    closedir(directory);
    return false;
}


//	struct serial_struct serinfo;
//	int	fd;
//
//	if ((fd = open(devicepath.c_str(), O_RDONLY|O_NONBLOCK)) < 0) {
//		cout << "Error opening " << devicepath << endl;
//		portFound = false;
//	} else {
//            serinfo.reserved_char[0] = 0;
//            if (ioctl(fd, TIOCGSERIAL, &serinfo) < 0) {
//                    cout << "Cannot get serial info" << endl;
//                    close(fd);
//                    portFound = false;
//            } else {
//                if(port == device){
//                    cout << "Port found" << endl;
//                    portFound = true;
//                }
//            }
//        }