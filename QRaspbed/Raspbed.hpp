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

private slots:
    void on_pushButton_clicked();

private:
    void runTestCli();

    Ui::Raspbed *ui;
};

#endif // RASPBED_HPP
