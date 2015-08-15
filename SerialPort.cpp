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
    struct dirent *entry = nullptr; // directory entries

    // The directory /sys/class/tty/ contains all serial devices
                cout << "Opening directory" << endl;
    directory = opendir("/sys/class/tty");

    // Make sure directory initialized
    if(directory == nullptr){
        cout << "ERROR! pdir could not be initialised correctly" << endl;
        exit(EXIT_FAILURE);
    }
    
    while (entry = readdir(directory))  {
        // Make sure directory initialized
        if(directory == nullptr){
            cout << "ERROR! pdir could not be initialised correctly" << endl;
            exit(EXIT_FAILURE);
        } else {
            cout << "Entry:" ;
            cout << entry->d_name << endl;
        }
    }
    // Close the directory
    closedir (directory);

    return true;
}