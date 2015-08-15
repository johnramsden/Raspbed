/* 
 * File:   main.cpp
 * Author: john
 *
 * Created on August 13, 2015, 6:06 PM
 */

#include <cstdlib>
#include "SerialPort.hpp"

using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {
    unique_ptr<SerialPort> port(new SerialPort);
    
    if(port->portExists("USB0")){
        cout << "Port exists!" << endl;
    } else {
        cout << "No port found." << endl;
    }
    
    
    return 0;
}

