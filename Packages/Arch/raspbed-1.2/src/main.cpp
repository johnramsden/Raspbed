/*
 * File:   main.cpp
 * Author: John Ramsden
 *
 * Created on August 18, 2015, 6:06 PM
 */

#include "Raspbed.hpp"
#include <QApplication>
#include <cstdlib>
#include "Bed.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationVersion(APP_VERSION);
    Raspbed w;
    w.show();
    return a.exec();
}
