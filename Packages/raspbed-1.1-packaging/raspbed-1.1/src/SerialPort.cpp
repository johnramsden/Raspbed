/*
 * File:   SerialPort.cpp
 * Author: John Ramsden
 * Email: ramsdenj@shaw.ca
 *
 * Created on August 18, 2015, 10:56 PM
 */

#include "SerialPort.hpp"

using namespace boost::asio;

SerialPort::SerialPort(std::string name)
    : SerialPort::SerialPort(
          name, 19200, serial_port_base::character_size(8),
          serial_port_base::stop_bits(serial_port_base::stop_bits::two),
          serial_port_base::parity(serial_port_base::parity::none),
          serial_port_base::flow_control(
              serial_port_base::flow_control::none)) {}

SerialPort::SerialPort(std::string name, unsigned int baud_rate,
                       serial_port_base::character_size character_size,
                       serial_port_base::stop_bits stop_bits,
                       serial_port_base::parity com_parity,
                       serial_port_base::flow_control flow_control)
    : portName(name), baudRate(serial_port_base::baud_rate(baud_rate)),
      characterSize(character_size), stopBits(stop_bits), parity(com_parity),
      flowControl(flow_control), io(), port(io) {}

SerialPort::~SerialPort() {}

bool SerialPort::open() {
    if (port.is_open()) {
        qDebug() << "Port is already opened, closing...";
        port.close();
    }

    if (portExists(portName)) {
        std::string fullName = "/dev/" + portName;
        qDebug() << "Opening " << QString::fromStdString(fullName);

        try {
            port.open(fullName);
        } catch (boost::system::system_error const &e) {
            qDebug() << "Warning: could not connect : " << e.what();
        }

        if (port.is_open()) {
            connected = true;
            qDebug() << "Connected";
            port.set_option(baudRate);
            port.set_option(characterSize);
            port.set_option(stopBits);
            port.set_option(parity);
            port.set_option(flowControl);
            return true;
        } else {
            qDebug() << "error : port isn't open...";
            connected = false;
            return false;
        }
    } else {
        qDebug() << "WARNING: Port " << QString::fromStdString(portName)
                 << " does not exist.";
        return false;
    }
}

void SerialPort::stop() {
    if (port.is_open()) {
        port.cancel();
        port.close();
        connected = false;
    }
    io.stop();
    io.reset();
    qDebug() << "\nPort closed.";
}

void SerialPort::write(const char *data) {
    std::size_t size = sizeof(data);

    try {
        boost::asio::write(port, boost::asio::buffer(data, size));
    } catch (boost::system::system_error const &e) {
        qDebug() << "Warning: Write error,  : " << e.what();
    }
}

void SerialPort::print() {
    qDebug() << "###################\nPort: "
             << QString::fromStdString(getPortName());
    qDebug() << "Baud rate: " << QString::number(getBaudRate().value());
    qDebug() << "Character size: "
             << QString::number(getCharacterSize().value());
    qDebug() << "Flow control: " << QString::number(getFlowControl().value());
    qDebug() << "Parity: " << QString::number(getParity().value());
    qDebug() << "Stop bits: " << QString::number(getStopBits().value());
    qDebug() << "###################";
}

bool SerialPort::portExists(std::string port) {
    std::vector<std::string> devices = getDevices();
    for (auto device : devices) {
        if (device == port) {
            qDebug() << "\nMATCH: Serial device '"
                     << QString::fromStdString(device) << "' found";
            return true;
        }
    }
    qDebug() << "\nNo match found.";
    return false;
}

std::vector<std::string> SerialPort::getDevices() {
    DIR *directory = nullptr;
    struct dirent *entry = nullptr;   // directory entry
    std::vector<std::string> devices; // List of devices

    // The directory /sys/class/tty contains all serial devices
    std::string portPath = "/sys/class/tty";

    directory = opendir(portPath.c_str());

    // Make sure directory initialized
    if (directory == nullptr) {
        qDebug() << "ERROR! pdir could not be initialised correctly";
        exit(EXIT_FAILURE);
    }

    // Get all devices in "/sys/class/tty"
    while ((entry = readdir(directory))) {
        // Make sure directory initialized
        if (directory == nullptr) {
            qDebug() << "ERROR! pdir could not be initialised correctly";
            exit(EXIT_FAILURE);
        } else {
            devices.push_back(entry->d_name);
        }
    }

    std::vector<std::string> ports;
    std::string deviceDriverPath;
    for (auto device : devices) {
        deviceDriverPath = portPath + "/" + device + "/device/driver";

        // Check for active devices
        DIR *driverDir = opendir(deviceDriverPath.c_str());
        if (driverDir) {
            ports.push_back(device);
            closedir(driverDir);
        }
    }
    closedir(directory);

    return ports;
}

void SerialPort::setFlowControl(
    boost::asio::serial_port_base::flow_control flowControl) {
    this->flowControl = flowControl;
}

boost::asio::serial_port_base::flow_control SerialPort::getFlowControl() const {
    return flowControl;
}

void SerialPort::setParity(boost::asio::serial_port_base::parity parity) {
    this->parity = parity;
}

boost::asio::serial_port_base::parity SerialPort::getParity() const {
    return parity;
}

void SerialPort::setStopBits(
    boost::asio::serial_port_base::stop_bits stopBits) {
    this->stopBits = stopBits;
}

boost::asio::serial_port_base::stop_bits SerialPort::getStopBits() const {
    return stopBits;
}

void SerialPort::setCharacterSize(
    boost::asio::serial_port_base::character_size characterSize) {
    this->characterSize = characterSize;
}

boost::asio::serial_port_base::character_size
SerialPort::getCharacterSize() const {
    return characterSize;
}

void SerialPort::setBaudRate(
    boost::asio::serial_port_base::baud_rate baudRate) {
    this->baudRate = baudRate;
}

boost::asio::serial_port_base::baud_rate SerialPort::getBaudRate() const {
    return baudRate;
}

void SerialPort::setPortName(std::string portName) {
    this->portName = portName;
}

std::string SerialPort::getPortName() const { return portName; }

void SerialPort::setConnected(bool connected) { this->connected = connected; }

bool SerialPort::isConnected() { return connected; }
