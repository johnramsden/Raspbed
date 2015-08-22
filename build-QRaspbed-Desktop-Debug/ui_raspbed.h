/********************************************************************************
** Form generated from reading UI file 'raspbed.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RASPBED_H
#define UI_RASPBED_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Raspbed
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *flattenBedButton;
    QPushButton *callButton;
    QPushButton *headUpButton;
    QPushButton *headDownButton;
    QPushButton *feetUpButton;
    QPushButton *feetDownButton;
    QPushButton *trendButton;
    QPushButton *bedUpButton;
    QPushButton *bedDownButton;
    QPushButton *lowerWheelsButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Raspbed)
    {
        if (Raspbed->objectName().isEmpty())
            Raspbed->setObjectName(QStringLiteral("Raspbed"));
        Raspbed->resize(1183, 699);
        centralWidget = new QWidget(Raspbed);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        flattenBedButton = new QPushButton(centralWidget);
        flattenBedButton->setObjectName(QStringLiteral("flattenBedButton"));

        gridLayout->addWidget(flattenBedButton, 0, 1, 1, 1);

        callButton = new QPushButton(centralWidget);
        callButton->setObjectName(QStringLiteral("callButton"));

        gridLayout->addWidget(callButton, 0, 2, 1, 1);

        headUpButton = new QPushButton(centralWidget);
        headUpButton->setObjectName(QStringLiteral("headUpButton"));
        headUpButton->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(headUpButton, 1, 0, 1, 1);

        headDownButton = new QPushButton(centralWidget);
        headDownButton->setObjectName(QStringLiteral("headDownButton"));

        gridLayout->addWidget(headDownButton, 1, 1, 1, 1);

        feetUpButton = new QPushButton(centralWidget);
        feetUpButton->setObjectName(QStringLiteral("feetUpButton"));

        gridLayout->addWidget(feetUpButton, 1, 2, 1, 1);

        feetDownButton = new QPushButton(centralWidget);
        feetDownButton->setObjectName(QStringLiteral("feetDownButton"));

        gridLayout->addWidget(feetDownButton, 1, 3, 1, 1);

        trendButton = new QPushButton(centralWidget);
        trendButton->setObjectName(QStringLiteral("trendButton"));

        gridLayout->addWidget(trendButton, 2, 0, 1, 1);

        bedUpButton = new QPushButton(centralWidget);
        bedUpButton->setObjectName(QStringLiteral("bedUpButton"));

        gridLayout->addWidget(bedUpButton, 2, 1, 1, 1);

        bedDownButton = new QPushButton(centralWidget);
        bedDownButton->setObjectName(QStringLiteral("bedDownButton"));

        gridLayout->addWidget(bedDownButton, 2, 2, 1, 1);

        lowerWheelsButton = new QPushButton(centralWidget);
        lowerWheelsButton->setObjectName(QStringLiteral("lowerWheelsButton"));

        gridLayout->addWidget(lowerWheelsButton, 2, 3, 1, 1);

        Raspbed->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Raspbed);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1183, 35));
        Raspbed->setMenuBar(menuBar);
        statusBar = new QStatusBar(Raspbed);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Raspbed->setStatusBar(statusBar);

        retranslateUi(Raspbed);

        QMetaObject::connectSlotsByName(Raspbed);
    } // setupUi

    void retranslateUi(QMainWindow *Raspbed)
    {
        Raspbed->setWindowTitle(QApplication::translate("Raspbed", "Raspbed", 0));
        flattenBedButton->setText(QString());
        callButton->setText(QString());
        headUpButton->setText(QString());
        headDownButton->setText(QString());
        feetUpButton->setText(QString());
        feetDownButton->setText(QString());
        trendButton->setText(QString());
        bedUpButton->setText(QString());
        bedDownButton->setText(QString());
        lowerWheelsButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Raspbed: public Ui_Raspbed {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RASPBED_H
