/********************************************************************************
** Form generated from reading UI file 'integ_abir_login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEG_ABIR_LOGIN_H
#define UI_INTEG_ABIR_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *login;
    QWidget *widget;
    QGroupBox *groupBox_2;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QLabel *label_3;
    QToolButton *toolButton_seConnecter;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QWidget *staff;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLabel *label;
    QComboBox *comboBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QToolButton *toolButton_9;
    QLineEdit *lineEdit_7;
    QLabel *label_11;
    QComboBox *comboBox;
    QWidget *widget_2;
    QTableWidget *tableWidget;
    QToolButton *toolButton_10;
    QToolButton *toolButton_11;
    QToolButton *toolButton_12;
    QToolButton *toolButton_14;
    QToolButton *toolButton_15;
    QWidget *tab_2;
    QGroupBox *groupBox_4;
    QLabel *label_12;
    QLabel *label_13;
    QGroupBox *groupBox_3;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QToolButton *toolButton_7;
    QToolButton *toolButton_8;
    QToolButton *toolButton_13;
    QLabel *label_10;
    QWidget *materiel;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QComboBox *comboBox_4;
    QWidget *widget_3;
    QTableWidget *tableWidget_2;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLineEdit *lineEdit_8;
    QGroupBox *groupBox_5;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_26;
    QToolButton *toolButton_16;
    QToolButton *toolButton_17;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QRadioButton *radioButton_7;
    QRadioButton *radioButton_8;
    QRadioButton *radioButton_9;
    QRadioButton *radioButton_10;
    QLabel *label_27;
    QToolButton *toolButton_18;
    QToolButton *toolButton_19;
    QToolButton *toolButton_20;
    QToolButton *toolButton_21;
    QToolButton *toolButton_22;
    QWidget *tab_4;
    QWidget *widget_4;
    QLabel *label_28;
    QLabel *label_29;
    QGroupBox *groupBox_6;
    QToolButton *toolButton_23;
    QToolButton *toolButton_24;
    QToolButton *toolButton_25;
    QToolButton *toolButton_26;
    QToolButton *toolButton_27;
    QToolButton *toolButton_28;
    QToolButton *toolButton_29;
    QLabel *label_30;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1109, 779);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 20, 1071, 681));
        login = new QWidget();
        login->setObjectName("login");
        widget = new QWidget(login);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(190, 80, 821, 521));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(189, 195, 199);"));
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(230, 50, 351, 421));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #F8C8DC;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top centre; \n"
"    padding: 10px 20px; \n"
"    border-radius: 15px; \n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    color: black; \n"
"    font-size: 20px; \n"
"    font-weight: bold;\n"
"}"));
        toolButton = new QToolButton(groupBox_2);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(10, 120, 41, 31));
        toolButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ContactNew));
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(30, 30));
        toolButton_2 = new QToolButton(groupBox_2);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(10, 240, 41, 31));
        toolButton_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::SystemLockScreen));
        toolButton_2->setIcon(icon1);
        toolButton_2->setIconSize(QSize(30, 30));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(210, 300, 121, 31));
        label_3->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        toolButton_seConnecter = new QToolButton(groupBox_2);
        toolButton_seConnecter->setObjectName("toolButton_seConnecter");
        toolButton_seConnecter->setGeometry(QRect(100, 340, 131, 51));
        toolButton_seConnecter->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 50, 91, 61));
        label_4->setStyleSheet(QString::fromUtf8("background-color:transparent;\n"
""));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(50, 120, 171, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(50, 240, 171, 31));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 180, 141, 31));
        label_2->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        stackedWidget->addWidget(login);
        staff = new QWidget();
        staff->setObjectName("staff");
        tabWidget = new QTabWidget(staff);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(170, 40, 911, 541));
        tabWidget->setStyleSheet(QString::fromUtf8("\n"
"QMainWindow, QWidget {\n"
"    background-color: #BDC3C7;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 15px;\n"
"    background-color: #BDC3C7;\n"
"}\n"
"\n"
"\n"
"QTabBar::tab {\n"
"    background: transparent;\n"
"    color: black;\n"
"    padding: 8px 20px;\n"
"    margin: 4px;\n"
"    border: 1px solid #999;\n"
"    border-radius: 15px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #95A5A6;        \n"
"    color: white;\n"
"}\n"
"\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #A7B1B1;         \n"
"    color: white;\n"
"}\n"
"\n"
"\n"
"QTabWidget > QWidget {\n"
"    background-color: #BDC3C7;\n"
"}\n"
""));
        tab = new QWidget();
        tab->setObjectName("tab");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 20, 211, 461));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top centre; \n"
"    padding: 10px 20px; \n"
"    border-radius: 15px; \n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: black; \n"
"    font-size: 20px; \n"
"    font-weight: bold;\n"
"\n"
"}\n"
""));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 100, 49, 16));
        label_5->setStyleSheet(QString::fromUtf8(" background: transparent;"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 150, 71, 16));
        label_6->setStyleSheet(QString::fromUtf8(" background: transparent;"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 200, 49, 21));
        label_7->setStyleSheet(QString::fromUtf8(" background: transparent;"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 340, 81, 21));
        label_8->setStyleSheet(QString::fromUtf8(" background: transparent;"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 260, 91, 21));
        label_9->setStyleSheet(QString::fromUtf8(" background: transparent;"));
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(20, 70, 113, 22));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(20, 120, 113, 22));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(20, 370, 113, 22));
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(20, 170, 113, 22));
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 50, 49, 16));
        label->setStyleSheet(QString::fromUtf8(" background: transparent;"));
        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(20, 230, 111, 22));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(10, 290, 89, 20));
        radioButton->setStyleSheet(QString::fromUtf8(" background: transparent;\n"
""));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(110, 290, 91, 20));
        radioButton_2->setStyleSheet(QString::fromUtf8(" background: transparent;"));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(70, 320, 89, 20));
        radioButton_3->setStyleSheet(QString::fromUtf8(" background: transparent;"));
        toolButton_9 = new QToolButton(groupBox);
        toolButton_9->setObjectName("toolButton_9");
        toolButton_9->setGeometry(QRect(60, 410, 91, 41));
        toolButton_9->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        lineEdit_7 = new QLineEdit(tab);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(270, 20, 113, 22));
        lineEdit_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_11 = new QLabel(tab);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(610, 20, 71, 21));
        comboBox = new QComboBox(tab);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(700, 20, 69, 22));
        comboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(230, 60, 611, 221));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 200, 220);"));
        tableWidget = new QTableWidget(widget_2);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(10, 10, 591, 201));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        toolButton_10 = new QToolButton(tab);
        toolButton_10->setObjectName("toolButton_10");
        toolButton_10->setGeometry(QRect(490, 10, 91, 41));
        toolButton_10->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_11 = new QToolButton(tab);
        toolButton_11->setObjectName("toolButton_11");
        toolButton_11->setGeometry(QRect(620, 290, 121, 41));
        toolButton_11->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_12 = new QToolButton(tab);
        toolButton_12->setObjectName("toolButton_12");
        toolButton_12->setGeometry(QRect(850, 170, 51, 41));
        toolButton_12->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        toolButton_12->setIcon(icon2);
        toolButton_12->setIconSize(QSize(30, 30));
        toolButton_14 = new QToolButton(tab);
        toolButton_14->setObjectName("toolButton_14");
        toolButton_14->setGeometry(QRect(850, 110, 51, 41));
        toolButton_14->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        toolButton_14->setIcon(icon3);
        toolButton_14->setIconSize(QSize(30, 30));
        toolButton_15 = new QToolButton(tab);
        toolButton_15->setObjectName("toolButton_15");
        toolButton_15->setGeometry(QRect(400, 10, 41, 41));
        toolButton_15->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::SystemSearch));
        toolButton_15->setIcon(icon4);
        toolButton_15->setIconSize(QSize(30, 30));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(40, 60, 431, 371));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top centre; \n"
"    padding: 10px 20px; \n"
"    border-radius: 15px; \n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: black; \n"
"    font-size: 20px; \n"
"    font-weight: bold;\n"
"\n"
"}\n"
""));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 50, 391, 301));
        label_12->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/WhatsApp Image 2025-10-02 at 15.59.50.jpeg")));
        label_12->setScaledContents(true);
        label_13 = new QLabel(tab_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(620, 230, 211, 61));
        label_13->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border: 2px solid #F8C8DC;\n"
"    border-radius: 15px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    color: black; \n"
"    font-weight: bold;\n"
"    padding: 10px;\n"
"    font-size: 16px;\n"
"}\n"
""));
        tabWidget->addTab(tab_2, QString());
        groupBox_3 = new QGroupBox(staff);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(30, 60, 141, 521));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top centre; \n"
"    padding: 10px 20px; \n"
"    border-radius: 15px; \n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: black; \n"
"    font-size: 20px; \n"
"    font-weight: bold;\n"
"\n"
"}"));
        toolButton_3 = new QToolButton(groupBox_3);
        toolButton_3->setObjectName("toolButton_3");
        toolButton_3->setGeometry(QRect(10, 170, 121, 41));
        toolButton_3->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_4 = new QToolButton(groupBox_3);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setGeometry(QRect(10, 210, 121, 41));
        toolButton_4->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_5 = new QToolButton(groupBox_3);
        toolButton_5->setObjectName("toolButton_5");
        toolButton_5->setGeometry(QRect(10, 400, 121, 41));
        toolButton_5->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_6 = new QToolButton(groupBox_3);
        toolButton_6->setObjectName("toolButton_6");
        toolButton_6->setGeometry(QRect(10, 350, 121, 41));
        toolButton_6->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_7 = new QToolButton(groupBox_3);
        toolButton_7->setObjectName("toolButton_7");
        toolButton_7->setGeometry(QRect(10, 250, 121, 41));
        toolButton_7->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_8 = new QToolButton(groupBox_3);
        toolButton_8->setObjectName("toolButton_8");
        toolButton_8->setGeometry(QRect(10, 300, 121, 41));
        toolButton_8->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_13 = new QToolButton(groupBox_3);
        toolButton_13->setObjectName("toolButton_13");
        toolButton_13->setGeometry(QRect(50, 460, 41, 41));
        toolButton_13->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::SystemShutdown));
        toolButton_13->setIcon(icon5);
        toolButton_13->setIconSize(QSize(30, 30));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(0, 40, 141, 121));
        label_10->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/WhatsApp_Image_2025-09-26_at_11.25.35-removebg-preview.png")));
        label_10->setScaledContents(true);
        stackedWidget->addWidget(staff);
        materiel = new QWidget();
        materiel->setObjectName("materiel");
        tabWidget_2 = new QTabWidget(materiel);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(200, 10, 811, 621));
        tabWidget_2->setStyleSheet(QString::fromUtf8("QMainWindow, QWidget {\n"
"    background-color: #BDC3C7;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 15px;\n"
"    background-color: #BDC3C7;\n"
"}\n"
"\n"
"\n"
"QTabBar::tab {\n"
"    background: transparent;\n"
"    color: black;\n"
"    padding: 8px 20px;\n"
"    margin: 4px;\n"
"    border: 1px solid #999;\n"
"    border-radius: 15px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #95A5A6;        \n"
"    color: white;\n"
"}\n"
"\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #A7B1B1;         \n"
"    color: white;\n"
"}\n"
"\n"
"\n"
"QTabWidget > QWidget {\n"
"    background-color: #BDC3C7;\n"
"}"));
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        comboBox_4 = new QComboBox(tab_3);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(350, 110, 151, 26));
        widget_3 = new QWidget(tab_3);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(250, 210, 431, 271));
        widget_3->setStyleSheet(QString::fromUtf8("background-color:rgb(248,200,220);"));
        tableWidget_2 = new QTableWidget(widget_3);
        if (tableWidget_2->columnCount() < 6)
            tableWidget_2->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        if (tableWidget_2->rowCount() < 5)
            tableWidget_2->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 3, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 4, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 2, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 3, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 4, __qtablewidgetitem27);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(10, 20, 411, 231));
        tableWidget_2->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        label_14 = new QLabel(widget_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(280, 270, 21, 31));
        label_14->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_14->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/gestion_des_projet/delete_78dp_0000F5_FILL0_wght400_GRAD0_opsz48.png")));
        label_14->setScaledContents(true);
        label_15 = new QLabel(widget_3);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(300, 270, 21, 31));
        label_15->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
""));
        label_15->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/gestion_des_projet/pencil.png")));
        label_15->setScaledContents(true);
        label_20 = new QLabel(widget_3);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(280, 340, 21, 31));
        label_20->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_20->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/gestion_des_projet/delete_78dp_0000F5_FILL0_wght400_GRAD0_opsz48.png")));
        label_20->setScaledContents(true);
        label_21 = new QLabel(widget_3);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(300, 340, 21, 31));
        label_21->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
""));
        label_21->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/gestion_des_projet/pencil.png")));
        label_21->setScaledContents(true);
        label_22 = new QLabel(widget_3);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(300, 310, 21, 31));
        label_22->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
""));
        label_22->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/gestion_des_projet/pencil.png")));
        label_22->setScaledContents(true);
        label_23 = new QLabel(widget_3);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(280, 310, 21, 31));
        label_23->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_23->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/gestion_des_projet/delete_78dp_0000F5_FILL0_wght400_GRAD0_opsz48.png")));
        label_23->setScaledContents(true);
        label_24 = new QLabel(widget_3);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(280, 380, 21, 31));
        label_24->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_24->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/gestion_des_projet/delete_78dp_0000F5_FILL0_wght400_GRAD0_opsz48.png")));
        label_24->setScaledContents(true);
        label_25 = new QLabel(widget_3);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(300, 380, 21, 31));
        label_25->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
""));
        label_25->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/gestion_des_projet/pencil.png")));
        label_25->setScaledContents(true);
        lineEdit_8 = new QLineEdit(tab_3);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(250, 170, 171, 26));
        lineEdit_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(0, 10, 241, 541));
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top centre; \n"
"    padding: 10px 20px; \n"
"    border-radius: 15px; \n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: black; \n"
"    font-size: 20px; \n"
"    font-weight: bold;\n"
"\n"
"}"));
        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(20, 40, 63, 20));
        label_16->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 90, 81, 31));
        label_17->setStyleSheet(QString::fromUtf8("background:transparent;\n"
""));
        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 150, 101, 31));
        label_18->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(0, 350, 101, 31));
        label_19->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_26 = new QLabel(groupBox_5);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 210, 91, 31));
        label_26->setStyleSheet(QString::fromUtf8("background:transparent;"));
        toolButton_16 = new QToolButton(groupBox_5);
        toolButton_16->setObjectName("toolButton_16");
        toolButton_16->setGeometry(QRect(0, 480, 101, 41));
        toolButton_16->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_17 = new QToolButton(groupBox_5);
        toolButton_17->setObjectName("toolButton_17");
        toolButton_17->setGeometry(QRect(120, 480, 101, 41));
        toolButton_17->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        lineEdit_9 = new QLineEdit(groupBox_5);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(10, 70, 161, 26));
        lineEdit_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_10 = new QLineEdit(groupBox_5);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(10, 120, 161, 26));
        lineEdit_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_11 = new QLineEdit(groupBox_5);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(10, 180, 161, 26));
        lineEdit_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        radioButton_4 = new QRadioButton(groupBox_5);
        radioButton_4->setObjectName("radioButton_4");
        radioButton_4->setGeometry(QRect(0, 240, 111, 25));
        radioButton_5 = new QRadioButton(groupBox_5);
        radioButton_5->setObjectName("radioButton_5");
        radioButton_5->setGeometry(QRect(0, 280, 141, 25));
        radioButton_6 = new QRadioButton(groupBox_5);
        radioButton_6->setObjectName("radioButton_6");
        radioButton_6->setGeometry(QRect(100, 320, 111, 25));
        radioButton_7 = new QRadioButton(groupBox_5);
        radioButton_7->setObjectName("radioButton_7");
        radioButton_7->setGeometry(QRect(120, 240, 111, 25));
        radioButton_8 = new QRadioButton(groupBox_5);
        radioButton_8->setObjectName("radioButton_8");
        radioButton_8->setGeometry(QRect(10, 390, 131, 25));
        radioButton_9 = new QRadioButton(groupBox_5);
        radioButton_9->setObjectName("radioButton_9");
        radioButton_9->setGeometry(QRect(30, 450, 121, 25));
        radioButton_10 = new QRadioButton(groupBox_5);
        radioButton_10->setObjectName("radioButton_10");
        radioButton_10->setGeometry(QRect(90, 420, 131, 25));
        label_27 = new QLabel(tab_3);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(260, 100, 91, 31));
        toolButton_18 = new QToolButton(tab_3);
        toolButton_18->setObjectName("toolButton_18");
        toolButton_18->setGeometry(QRect(440, 150, 51, 51));
        toolButton_18->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	font: 10pt \"Segoe UI\";\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        toolButton_18->setIcon(icon6);
        toolButton_18->setIconSize(QSize(30, 30));
        toolButton_19 = new QToolButton(tab_3);
        toolButton_19->setObjectName("toolButton_19");
        toolButton_19->setGeometry(QRect(250, 480, 201, 41));
        toolButton_19->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_20 = new QToolButton(tab_3);
        toolButton_20->setObjectName("toolButton_20");
        toolButton_20->setGeometry(QRect(510, 140, 121, 61));
        toolButton_20->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_21 = new QToolButton(tab_3);
        toolButton_21->setObjectName("toolButton_21");
        toolButton_21->setGeometry(QRect(700, 290, 81, 51));
        toolButton_21->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	font: 10pt \"Segoe UI\";\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        toolButton_21->setIcon(icon2);
        toolButton_21->setIconSize(QSize(30, 30));
        toolButton_22 = new QToolButton(tab_3);
        toolButton_22->setObjectName("toolButton_22");
        toolButton_22->setGeometry(QRect(700, 220, 71, 51));
        toolButton_22->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	font: 10pt \"Segoe UI\";\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        toolButton_22->setIcon(icon3);
        toolButton_22->setIconSize(QSize(30, 30));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        widget_4 = new QWidget(tab_4);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(30, 40, 501, 511));
        label_28 = new QLabel(widget_4);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(0, 10, 501, 481));
        label_28->setPixmap(QPixmap(QString::fromUtf8("../materiel123/1.png")));
        label_28->setScaledContents(true);
        label_29 = new QLabel(tab_4);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(740, 110, 231, 311));
        label_29->setPixmap(QPixmap(QString::fromUtf8("../materiel123/frame.png")));
        label_29->setScaledContents(true);
        tabWidget_2->addTab(tab_4, QString());
        groupBox_6 = new QGroupBox(materiel);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(30, 50, 151, 561));
        groupBox_6->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top centre; \n"
"    padding: 10px 20px; \n"
"    border-radius: 15px; \n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: black; \n"
"    font-size: 20px; \n"
"    font-weight: bold;\n"
"\n"
"}"));
        toolButton_23 = new QToolButton(groupBox_6);
        toolButton_23->setObjectName("toolButton_23");
        toolButton_23->setGeometry(QRect(10, 170, 121, 41));
        toolButton_23->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_24 = new QToolButton(groupBox_6);
        toolButton_24->setObjectName("toolButton_24");
        toolButton_24->setGeometry(QRect(10, 210, 121, 41));
        toolButton_24->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_25 = new QToolButton(groupBox_6);
        toolButton_25->setObjectName("toolButton_25");
        toolButton_25->setGeometry(QRect(10, 400, 121, 41));
        toolButton_25->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_26 = new QToolButton(groupBox_6);
        toolButton_26->setObjectName("toolButton_26");
        toolButton_26->setGeometry(QRect(10, 350, 121, 41));
        toolButton_26->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_27 = new QToolButton(groupBox_6);
        toolButton_27->setObjectName("toolButton_27");
        toolButton_27->setGeometry(QRect(10, 250, 121, 41));
        toolButton_27->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_28 = new QToolButton(groupBox_6);
        toolButton_28->setObjectName("toolButton_28");
        toolButton_28->setGeometry(QRect(10, 300, 121, 41));
        toolButton_28->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}\n"
""));
        toolButton_29 = new QToolButton(groupBox_6);
        toolButton_29->setObjectName("toolButton_29");
        toolButton_29->setGeometry(QRect(50, 460, 41, 41));
        toolButton_29->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 5px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F8C8DC,\n"
"                                stop:1 #BDC3C7);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"    color: black;\n"
"}\n"
""));
        toolButton_29->setIcon(icon5);
        toolButton_29->setIconSize(QSize(30, 30));
        label_30 = new QLabel(groupBox_6);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(0, 40, 141, 121));
        label_30->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/WhatsApp_Image_2025-09-26_at_11.25.35-removebg-preview.png")));
        label_30->setScaledContents(true);
        stackedWidget->addWidget(materiel);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1109, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#ff0000;\">Mot de passe oubli\303\251?</span></p></body></html>", nullptr));
        toolButton_seConnecter->setText(QCoreApplication::translate("MainWindow", "se connecter", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#000000;\">Id unique</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#000000;\">Mot de passe</span></p></body></html>", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Ajouter un staff technique", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Nom</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Prenom</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">poste</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Telephone</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Competence</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Id</span></p></body></html>", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Staff technique", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Client", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Materiel", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "Projet", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("MainWindow", "Sponsor", nullptr));
        comboBox_2->setItemText(5, QCoreApplication::translate("MainWindow", "Createur", nullptr));

        radioButton->setText(QCoreApplication::translate("MainWindow", "D\303\251butant", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Interm\303\251diaire", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Avanc\303\251", nullptr));
        toolButton_9->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        lineEdit_7->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Trier par:</span></p></body></html>", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Poste", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Competence", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Competence", nullptr));
        toolButton_10->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        toolButton_11->setText(QCoreApplication::translate("MainWindow", "Exportation pdf", nullptr));
        toolButton_12->setText(QString());
        toolButton_14->setText(QString());
        toolButton_15->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Acceuil", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Statistiques des staff techniques selon leurs postes", nullptr));
        label_12->setText(QString());
        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; color:#ffffff;\">Autres Metiers =&gt;</span></p><p align=\"center\"><span style=\" color:#ffffff;\"><br/></span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Fonctionnalites", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_3->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">neocreate</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Neocreate", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "Staff technique", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        toolButton_5->setText(QCoreApplication::translate("MainWindow", "Createur", nullptr));
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "Sponsor", nullptr));
        toolButton_7->setText(QCoreApplication::translate("MainWindow", "Materiel", nullptr));
        toolButton_8->setText(QCoreApplication::translate("MainWindow", "Projet", nullptr));
        toolButton_13->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_10->setText(QString());
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "Type", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "Etat", nullptr));

        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Eat", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Localisation", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Responsable", nullptr));

        const bool __sortingEnabled = tableWidget_2->isSortingEnabled();
        tableWidget_2->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_2->item(0, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "MAT 001", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_2->item(0, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "camera sony", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_2->item(0, 2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "vid\303\251o", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_2->item(0, 3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "en panne", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_2->item(0, 4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "salle de montage", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_2->item(0, 5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "adiminstrateu", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_2->item(1, 0);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "MAT 002", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_2->item(1, 1);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "webcom", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_2->item(1, 2);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "vid\303\251o", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_2->item(1, 3);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Fonctioonnel", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_2->item(1, 4);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "salle de podcast", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_2->item(2, 0);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "MAT 003", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_2->item(2, 1);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Micro", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_2->item(2, 2);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Audio", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_2->item(2, 3);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "en maintenance", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_2->item(2, 4);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "salle tournage", nullptr));
        tableWidget_2->setSortingEnabled(__sortingEnabled);

        label_14->setText(QString());
        label_15->setText(QString());
        label_20->setText(QString());
        label_21->setText(QString());
        label_22->setText(QString());
        label_23->setText(QString());
        label_24->setText(QString());
        label_25->setText(QString());
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Ajouer un materiel", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Id</span></p></body></html>", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Nom</span></p></body></html>", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Type</span></p></body></html>", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Localisation</span></p></body></html>", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Etat</span></p></body></html>", nullptr));
        toolButton_16->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        toolButton_17->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "Fonctionnel", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MainWindow", "en maintenance", nullptr));
        radioButton_6->setText(QCoreApplication::translate("MainWindow", "hors sevice", nullptr));
        radioButton_7->setText(QCoreApplication::translate("MainWindow", "en panne", nullptr));
        radioButton_8->setText(QCoreApplication::translate("MainWindow", "studio tournage", nullptr));
        radioButton_9->setText(QCoreApplication::translate("MainWindow", "salle podcast", nullptr));
        radioButton_10->setText(QCoreApplication::translate("MainWindow", "salle montage", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Trier par:</span></p></body></html>", nullptr));
        toolButton_18->setText(QString());
        toolButton_19->setText(QCoreApplication::translate("MainWindow", "exportation pdf", nullptr));
        toolButton_20->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        toolButton_21->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        toolButton_22->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindow", " Acceuil", nullptr));
        label_28->setText(QString());
        label_29->setText(QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_6->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">neocreate</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Neocreate", nullptr));
        toolButton_23->setText(QCoreApplication::translate("MainWindow", "Staff technique", nullptr));
        toolButton_24->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        toolButton_25->setText(QCoreApplication::translate("MainWindow", "Createur", nullptr));
        toolButton_26->setText(QCoreApplication::translate("MainWindow", "Sponsor", nullptr));
        toolButton_27->setText(QCoreApplication::translate("MainWindow", "Materiel", nullptr));
        toolButton_28->setText(QCoreApplication::translate("MainWindow", "Projet", nullptr));
        toolButton_29->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_30->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEG_ABIR_LOGIN_H
