/* 
 * File:   Bed.hpp
 * Author: john
 *
 * Created on August 17, 2015, 1:30 PM
 */

#ifndef BED_HPP
#define	BED_HPP

#include <iostream>

class Bed {
public:
    Bed();
    Bed(const Bed& orig);
    virtual ~Bed();
    
    // 1,0,{relay} is on
    char command(const char relay, bool on);
    
    struct Relay {
        void print();
        const char close_all = 0;
        const char head_up = 1;
        const char head_down = 2;
        const char feet_up = 3;
        const char feet_down = 4;
        const char trend_up = 5;
        const char bed_up = 6;
        const char bed_down = 7;
        const char lower_wheels = 8;
    } relay;
    // Relay bedCommand;
private:

};

#endif	/* BED_HPP */

