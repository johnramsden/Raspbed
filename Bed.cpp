/* 
 * File:   Bed.cpp
 * Author: john
 * 
 * Created on August 17, 2015, 1:30 PM
 */

#include "Bed.hpp"

Bed::Bed() {
}

Bed::Bed(const Bed& orig) {
}

Bed::~Bed() {
}

char Bed::command(const char relay, bool on){
    // 1,0,{relay} is on
    if(on){
        return 100 + relay;
    } else{
        return 110 + relay;
    }
}