#include "Raspbed.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Raspbed w;
    w.show();

    return a.exec();
}
