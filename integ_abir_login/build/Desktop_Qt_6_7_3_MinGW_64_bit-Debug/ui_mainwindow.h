/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

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
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1201, 779);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 20, 1151, 681));
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
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1201, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
