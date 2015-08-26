/*
 * File:   main.cpp
 * Author: John Ramsden
 *
 * Created on August 18, 2015, 6:06 PM
 */

#include "Raspbed.hpp"
#include <QApplication>
#include <cstdlib>
#include "MouseFilter.hpp"
#include "Bed.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Raspbed w;
    w.installEventFilter(new MouseFilter());
    w.show();
    return a.exec();
}
