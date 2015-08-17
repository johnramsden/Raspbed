/* 
 * File:   main.cpp
 * Author: John Ramsden
 *
 * Created on August 13, 2015, 6:06 PM
 */

#include <cstdlib>
#include "SerialPort.hpp"
#include "SimpleSerial.hpp"

using namespace std;


//      0 - Close all
//      1: Head up
//      2: Head down
//      3: Feet up
//      4: Feet down
//      5: Trend up
//      6: Bed up
//      7: Bed down
//      8: Set wheels

int main(int argc, char** argv) {
    try {
        SimpleSerial serialPort("ttyUSB0");
        serialPort.print();
        serialPort.open();


        
        serialPort.write(values, sizeof(values));
        sleep(2);
        
        values[0] = {111};
        serialPort.write(values, sizeof(values));
        
        serialPort.stop();
    } catch (boost::system::system_error& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}