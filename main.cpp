/* 
 * File:   main.cpp
 * Author: john
 *
 * Created on August 13, 2015, 6:06 PM
 */

#include <cstdlib>
#include "SerialPort.hpp"

using namespace std;

int main(int argc, char** argv) {
    try {
        SerialPort serialPort("ttyUSB0");
        serialPort.print();
        serialPort.start();

        //Binary test
        char values[] = {1, 0, 2};
        serialPort.write(values, sizeof (values));
        sleep(5*1000);
        serialPort.stop();
    } catch (boost::system::system_error& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}