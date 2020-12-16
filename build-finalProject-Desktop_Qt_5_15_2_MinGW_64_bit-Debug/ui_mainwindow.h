/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *loadDataButton;
    QProgressBar *UIprogressBar;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_11;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QSpinBox *spinBox;
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QGridLayout *gridLayout_2;
    QCheckBox *origLngBox;
    QCheckBox *destLngBox;
    QCheckBox *depTimeBox;
    QCheckBox *orderIDBox;
    QCheckBox *feeBox;
    QCheckBox *endTimeBox;
    QCheckBox *origLatBox;
    QCheckBox *destLatBox;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_4;
    QDateTimeEdit *startTimeEdit;
    QLabel *label_5;
    QDateTimeEdit *endTimeEdit;
    QLabel *label_6;
    QComboBox *comboBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QChartView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1159, 404);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        loadDataButton = new QPushButton(centralwidget);
        loadDataButton->setObjectName(QString::fromUtf8("loadDataButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(loadDataButton->sizePolicy().hasHeightForWidth());
        loadDataButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(loadDataButton);

        UIprogressBar = new QProgressBar(centralwidget);
        UIprogressBar->setObjectName(QString::fromUtf8("UIprogressBar"));
        sizePolicy1.setHeightForWidth(UIprogressBar->sizePolicy().hasHeightForWidth());
        UIprogressBar->setSizePolicy(sizePolicy1);
        UIprogressBar->setValue(0);

        verticalLayout->addWidget(UIprogressBar);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_7->setFont(font1);

        verticalLayout_9->addWidget(label_7);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        radioButton_2 = new QRadioButton(centralwidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButton_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        sizePolicy1.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy1);

        verticalLayout_11->addWidget(radioButton_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton = new QRadioButton(centralwidget);
        buttonGroup->addButton(radioButton);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        sizePolicy1.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(radioButton);

        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout->addWidget(spinBox);


        verticalLayout_11->addLayout(horizontalLayout);


        verticalLayout_9->addLayout(verticalLayout_11);


        gridLayout->addLayout(verticalLayout_9, 1, 0, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setFont(font1);

        verticalLayout_7->addWidget(label);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        origLngBox = new QCheckBox(centralwidget);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(origLngBox);
        origLngBox->setObjectName(QString::fromUtf8("origLngBox"));

        gridLayout_2->addWidget(origLngBox, 2, 0, 1, 1);

        destLngBox = new QCheckBox(centralwidget);
        buttonGroup_2->addButton(destLngBox);
        destLngBox->setObjectName(QString::fromUtf8("destLngBox"));

        gridLayout_2->addWidget(destLngBox, 3, 0, 1, 1);

        depTimeBox = new QCheckBox(centralwidget);
        buttonGroup_2->addButton(depTimeBox);
        depTimeBox->setObjectName(QString::fromUtf8("depTimeBox"));

        gridLayout_2->addWidget(depTimeBox, 1, 0, 1, 1);

        orderIDBox = new QCheckBox(centralwidget);
        buttonGroup_2->addButton(orderIDBox);
        orderIDBox->setObjectName(QString::fromUtf8("orderIDBox"));

        gridLayout_2->addWidget(orderIDBox, 0, 0, 1, 1);

        feeBox = new QCheckBox(centralwidget);
        buttonGroup_2->addButton(feeBox);
        feeBox->setObjectName(QString::fromUtf8("feeBox"));

        gridLayout_2->addWidget(feeBox, 0, 1, 1, 1);

        endTimeBox = new QCheckBox(centralwidget);
        buttonGroup_2->addButton(endTimeBox);
        endTimeBox->setObjectName(QString::fromUtf8("endTimeBox"));

        gridLayout_2->addWidget(endTimeBox, 1, 1, 1, 1);

        origLatBox = new QCheckBox(centralwidget);
        buttonGroup_2->addButton(origLatBox);
        origLatBox->setObjectName(QString::fromUtf8("origLatBox"));

        gridLayout_2->addWidget(origLatBox, 2, 1, 1, 1);

        destLatBox = new QCheckBox(centralwidget);
        buttonGroup_2->addButton(destLatBox);
        destLatBox->setObjectName(QString::fromUtf8("destLatBox"));

        gridLayout_2->addWidget(destLatBox, 3, 1, 1, 1);


        verticalLayout_7->addLayout(gridLayout_2);


        gridLayout->addLayout(verticalLayout_7, 0, 0, 1, 1);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setFont(font1);

        verticalLayout_10->addWidget(label_2);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        verticalLayout_8->addWidget(label_4);

        startTimeEdit = new QDateTimeEdit(centralwidget);
        startTimeEdit->setObjectName(QString::fromUtf8("startTimeEdit"));

        verticalLayout_8->addWidget(startTimeEdit);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        verticalLayout_8->addWidget(label_5);

        endTimeEdit = new QDateTimeEdit(centralwidget);
        endTimeEdit->setObjectName(QString::fromUtf8("endTimeEdit"));

        verticalLayout_8->addWidget(endTimeEdit);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);

        verticalLayout_8->addWidget(label_6);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_8->addWidget(comboBox);


        verticalLayout_10->addLayout(verticalLayout_8);


        gridLayout->addLayout(verticalLayout_10, 0, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setFont(font1);

        verticalLayout_4->addWidget(label_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout_2->addWidget(pushButton_4);


        verticalLayout_4->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        graphicsView = new QChartView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout_3->addWidget(graphicsView, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1159, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loadDataButton->setText(QCoreApplication::translate("MainWindow", "Load data", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Choose area", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "all Chengdu", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "grid", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Choose data fields", nullptr));
        origLngBox->setText(QCoreApplication::translate("MainWindow", "orig_lng", nullptr));
        destLngBox->setText(QCoreApplication::translate("MainWindow", "dest_lng", nullptr));
        depTimeBox->setText(QCoreApplication::translate("MainWindow", "departure_time", nullptr));
        orderIDBox->setText(QCoreApplication::translate("MainWindow", "order_id", nullptr));
        feeBox->setText(QCoreApplication::translate("MainWindow", "fee", nullptr));
        endTimeBox->setText(QCoreApplication::translate("MainWindow", "end_time", nullptr));
        origLatBox->setText(QCoreApplication::translate("MainWindow", "orig_lat", nullptr));
        destLatBox->setText(QCoreApplication::translate("MainWindow", "dest_lat", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Choose time", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Start time", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "End time", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Time step", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "1 minute", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "10 minute", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "30 minute", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "1 hour", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "12 hour", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("MainWindow", "1 day", nullptr));
        comboBox->setItemText(6, QString());

        label_3->setText(QCoreApplication::translate("MainWindow", "Choose what to display", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
