/********************************************************************************
** Form generated from reading UI file 'robotcontest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTCONTEST_H
#define UI_ROBOTCONTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotContestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer;
    QTextBrowser *textBrowser;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RobotContestClass)
    {
        if (RobotContestClass->objectName().isEmpty())
            RobotContestClass->setObjectName(QStringLiteral("RobotContestClass"));
        RobotContestClass->resize(702, 631);
        centralWidget = new QWidget(RobotContestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setContextMenuPolicy(Qt::DefaultContextMenu);
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setMode(QLCDNumber::Dec);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(1));
        lcdNumber->setProperty("intValue", QVariant(1));

        gridLayout_3->addWidget(lcdNumber, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 0, 1, 2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 0, 1, 1);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 2, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(48, 158, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout->addItem(verticalSpacer);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        horizontalLayout->addWidget(textBrowser);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 0, 3, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 0, 4, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 0, 5, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_2->addWidget(lineEdit_2, 1, 1, 1, 1);

        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_2->addWidget(lineEdit_3, 1, 2, 1, 1);

        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_2->addWidget(lineEdit_4, 1, 3, 1, 1);

        lineEdit_5 = new QLineEdit(centralWidget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout_2->addWidget(lineEdit_5, 1, 4, 1, 1);

        lineEdit_6 = new QLineEdit(centralWidget);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        gridLayout_2->addWidget(lineEdit_6, 1, 5, 1, 1);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 1, 1, 1);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout_2->addWidget(pushButton_6, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(228, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 3, 1, 2);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_2->addWidget(pushButton_7, 2, 5, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 3, 0, 1, 1);

        RobotContestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RobotContestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 702, 26));
        RobotContestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RobotContestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RobotContestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RobotContestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RobotContestClass->setStatusBar(statusBar);

        retranslateUi(RobotContestClass);

        QMetaObject::connectSlotsByName(RobotContestClass);
    } // setupUi

    void retranslateUi(QMainWindow *RobotContestClass)
    {
        RobotContestClass->setWindowTitle(QApplication::translate("RobotContestClass", "RobotContest", Q_NULLPTR));
        label->setText(QApplication::translate("RobotContestClass", "TextLabel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("RobotContestClass", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("RobotContestClass", "PushButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("RobotContestClass", "PushButton", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("RobotContestClass", "PushButton", Q_NULLPTR));
        label_2->setText(QApplication::translate("RobotContestClass", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("RobotContestClass", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("RobotContestClass", "TextLabel", Q_NULLPTR));
        label_5->setText(QApplication::translate("RobotContestClass", "TextLabel", Q_NULLPTR));
        label_6->setText(QApplication::translate("RobotContestClass", "TextLabel", Q_NULLPTR));
        label_7->setText(QApplication::translate("RobotContestClass", "TextLabel", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("RobotContestClass", "PushButton", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("RobotContestClass", "PushButton", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("RobotContestClass", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RobotContestClass: public Ui_RobotContestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTCONTEST_H
