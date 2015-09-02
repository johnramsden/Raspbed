/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *serialPortHorizontalLayout;
    QLabel *serialPortLabel;
    QComboBox *serialPortComboBox;
    QHBoxLayout *callContactHorizontalLayout;
    QLabel *callContactLabel;
    QLineEdit *callContactLineEdit;
    QHBoxLayout *callContactHorizontalLayout_2;
    QLabel *holdTimeLabel;
    QLineEdit *buttonHoldTimeEdit;
    QCheckBox *iconStyleCheckBox;
    QCheckBox *buttonModeCheckBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QStringLiteral("Settings"));
        Settings->resize(400, 382);
        verticalLayout = new QVBoxLayout(Settings);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        serialPortHorizontalLayout = new QHBoxLayout();
        serialPortHorizontalLayout->setObjectName(QStringLiteral("serialPortHorizontalLayout"));
        serialPortLabel = new QLabel(Settings);
        serialPortLabel->setObjectName(QStringLiteral("serialPortLabel"));

        serialPortHorizontalLayout->addWidget(serialPortLabel);

        serialPortComboBox = new QComboBox(Settings);
        serialPortComboBox->setObjectName(QStringLiteral("serialPortComboBox"));

        serialPortHorizontalLayout->addWidget(serialPortComboBox);


        verticalLayout->addLayout(serialPortHorizontalLayout);

        callContactHorizontalLayout = new QHBoxLayout();
        callContactHorizontalLayout->setObjectName(QStringLiteral("callContactHorizontalLayout"));
        callContactLabel = new QLabel(Settings);
        callContactLabel->setObjectName(QStringLiteral("callContactLabel"));

        callContactHorizontalLayout->addWidget(callContactLabel);

        callContactLineEdit = new QLineEdit(Settings);
        callContactLineEdit->setObjectName(QStringLiteral("callContactLineEdit"));

        callContactHorizontalLayout->addWidget(callContactLineEdit);


        verticalLayout->addLayout(callContactHorizontalLayout);

        callContactHorizontalLayout_2 = new QHBoxLayout();
        callContactHorizontalLayout_2->setObjectName(QStringLiteral("callContactHorizontalLayout_2"));
        holdTimeLabel = new QLabel(Settings);
        holdTimeLabel->setObjectName(QStringLiteral("holdTimeLabel"));

        callContactHorizontalLayout_2->addWidget(holdTimeLabel);

        buttonHoldTimeEdit = new QLineEdit(Settings);
        buttonHoldTimeEdit->setObjectName(QStringLiteral("buttonHoldTimeEdit"));

        callContactHorizontalLayout_2->addWidget(buttonHoldTimeEdit);


        verticalLayout->addLayout(callContactHorizontalLayout_2);

        iconStyleCheckBox = new QCheckBox(Settings);
        iconStyleCheckBox->setObjectName(QStringLiteral("iconStyleCheckBox"));

        verticalLayout->addWidget(iconStyleCheckBox);

        buttonModeCheckBox = new QCheckBox(Settings);
        buttonModeCheckBox->setObjectName(QStringLiteral("buttonModeCheckBox"));

        verticalLayout->addWidget(buttonModeCheckBox);

        buttonBox = new QDialogButtonBox(Settings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Settings);
        QObject::connect(buttonBox, SIGNAL(accepted()), Settings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Dialog", 0));
        serialPortLabel->setText(QApplication::translate("Settings", "Serial Port:", 0));
#ifndef QT_NO_TOOLTIP
        serialPortComboBox->setToolTip(QApplication::translate("Settings", "<html><head/><body><p>Serial Port</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        serialPortComboBox->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        serialPortComboBox->setCurrentText(QString());
        callContactLabel->setText(QApplication::translate("Settings", "Call Contact:", 0));
        holdTimeLabel->setText(QApplication::translate("Settings", "Sip n Puff Hold Time (s):", 0));
        iconStyleCheckBox->setText(QApplication::translate("Settings", "Use Border Style Icons", 0));
        buttonModeCheckBox->setText(QApplication::translate("Settings", "Button Mode", 0));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
