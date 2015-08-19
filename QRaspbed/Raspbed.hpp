#ifndef RASPBED_HPP
#define RASPBED_HPP

#include <QMainWindow>

namespace Ui {
class Raspbed;
}

class Raspbed : public QMainWindow
{
    Q_OBJECT

public:
    explicit Raspbed(QWidget *parent = 0);
    ~Raspbed();

private:
    Ui::Raspbed *ui;
};

#endif // RASPBED_HPP
