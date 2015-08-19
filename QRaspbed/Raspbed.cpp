#include "Raspbed.hpp"
#include "ui_raspbed.h"
#include "SerialPort.hpp"
#include "Bed.hpp"

Raspbed::Raspbed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Raspbed)
{
    ui->setupUi(this);
}

Raspbed::~Raspbed()
{
    delete ui;
}

void Raspbed::runTestCli(){
    try {
         SerialPort serialPort("ttyUSB0");
         Bed bed{};
         // serialPort.print();
         serialPort.open();
                 char comm = 1;
                 char values[1];
                 values[0] = bed.command(comm, true);
                 serialPort.write(values, sizeof(values));
                 sleep(2);
                 values[0] = bed.command(comm, false);
                 serialPort.write(values, sizeof(values));
         serialPort.stop();

     } catch (boost::system::system_error& e) {
         //cout << "Error: " << e.what() << endl;
     }
}

void Raspbed::on_pushButton_clicked()
{
    runTestCli();
}
