/* 
 * File:   main.cpp
 * Author: John Ramsden
 *
 * Created on August 13, 2015, 6:06 PM
 */

#include <cstdlib>
#include "SerialPort.hpp"
#include "SerialPort.hpp"
#include "Bed.hpp"
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
        SerialPort serialPort("ttyUSB0");
        Bed bed{};
        serialPort.print();
        serialPort.open();
        
        int input;
        while(true){
            bed.relay.print();
            cout << "-------------------\nEnter command (-1 to exit): ";
            cin >> input;
            
            if((input >= 0) && (input <= 8)){
                char comm = static_cast<char>(input);
                char values[1];
                values[0] = bed.command(comm, true);
                serialPort.write(values, sizeof(values));
                sleep(2);
                values[0] = bed.command(comm, false);
                serialPort.write(values, sizeof(values));
            } else if(input == -1){
                cout << "Exiting..." << endl;
                break;
            } else {
                cout << "Not supported, try again." << endl;
            }
        }
        serialPort.stop();
        
    } catch (boost::system::system_error& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}