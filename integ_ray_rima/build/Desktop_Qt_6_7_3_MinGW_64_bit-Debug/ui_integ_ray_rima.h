/********************************************************************************
** Form generated from reading UI file 'integ_ray_rima.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEG_RAY_RIMA_H
#define UI_INTEG_RAY_RIMA_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_integ_ray_rima
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *projet;
    QGroupBox *groupBox;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QToolButton *toolButton_11;
    QLabel *label_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QComboBox *comboBox_4;
    QWidget *widget_2;
    QTableWidget *tableWidget_2;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLineEdit *lineEdit_4;
    QGroupBox *groupBox_3;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QComboBox *comboBox_5;
    QComboBox *comboBox_6;
    QLabel *label_16;
    QToolButton *toolButton_15;
    QToolButton *toolButton_16;
    QLineEdit *lineEdit_5;
    QDateEdit *dateEdit_3;
    QDateEdit *dateEdit_4;
    QLineEdit *lineEdit_6;
    QLabel *label_17;
    QToolButton *toolButton_17;
    QToolButton *toolButton_18;
    QToolButton *toolButton_19;
    QToolButton *toolButton_20;
    QToolButton *toolButton_21;
    QWidget *tab_2;
    QGroupBox *groupBox_statistics;
    QLabel *label_period_title;
    QComboBox *comboBox_period;
    QLabel *label_summary_title;
    QFrame *frame_broadcast;
    QVBoxLayout *verticalLayout;
    QLabel *label_broadcast_title;
    QLabel *label_broadcast_count;
    QLabel *label_broadcast_subtitle;
    QFrame *frame_live;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_live_title;
    QLabel *label_live_count;
    QLabel *label_live_subtitle;
    QFrame *frame_youtube;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_youtube_title;
    QLabel *label_youtube_count;
    QLabel *label_youtube_subtitle;
    QFrame *frame_total;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_total_title;
    QLabel *label_total_count;
    QLabel *label_total_subtitle;
    QWidget *sponsor;
    QGroupBox *groupBox_2;
    QToolButton *toolButton_7;
    QToolButton *toolButton_8;
    QToolButton *toolButton_9;
    QToolButton *toolButton_10;
    QToolButton *toolButton_12;
    QToolButton *toolButton_13;
    QToolButton *toolButton_14;
    QLabel *label_3;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QGroupBox *groupBox_4;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_18;
    QLabel *label_19;
    QComboBox *comboBox_2;
    QLabel *label_26;
    QDateEdit *dateEdit_5;
    QDateEdit *dateEdit_6;
    QLabel *label_27;
    QLineEdit *lineEdit_2;
    QToolButton *toolButton_22;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QToolButton *toolButton_23;
    QLineEdit *lineEdit_9;
    QLabel *label_28;
    QComboBox *comboBox_7;
    QWidget *widget_3;
    QTableWidget *tableWidget_3;
    QToolButton *toolButton_24;
    QToolButton *toolButton_25;
    QToolButton *toolButton_26;
    QToolButton *toolButton_27;
    QGroupBox *groupBox_5;
    QLabel *label_5;
    QWidget *tab_4;
    QGroupBox *groupBox_6;
    QLabel *label_6;
    QLabel *label_7;
    QGroupBox *groupBox_7;
    QToolButton *toolButton_28;
    QToolButton *toolButton_29;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *integ_ray_rima)
    {
        if (integ_ray_rima->objectName().isEmpty())
            integ_ray_rima->setObjectName("integ_ray_rima");
        integ_ray_rima->resize(1301, 761);
        centralwidget = new QWidget(integ_ray_rima);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 20, 1241, 671));
        projet = new QWidget();
        projet->setObjectName("projet");
        groupBox = new QGroupBox(projet);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 20, 211, 611));
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
"}"));
        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(20, 170, 171, 51));
        toolButton->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(20, 430, 171, 51));
        toolButton_2->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_3 = new QToolButton(groupBox);
        toolButton_3->setObjectName("toolButton_3");
        toolButton_3->setGeometry(QRect(20, 360, 161, 51));
        toolButton_3->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_4 = new QToolButton(groupBox);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setGeometry(QRect(20, 290, 171, 51));
        toolButton_4->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_5 = new QToolButton(groupBox);
        toolButton_5->setObjectName("toolButton_5");
        toolButton_5->setGeometry(QRect(20, 230, 171, 51));
        toolButton_5->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_6 = new QToolButton(groupBox);
        toolButton_6->setObjectName("toolButton_6");
        toolButton_6->setGeometry(QRect(20, 490, 171, 51));
        toolButton_6->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_11 = new QToolButton(groupBox);
        toolButton_11->setObjectName("toolButton_11");
        toolButton_11->setGeometry(QRect(70, 550, 61, 51));
        toolButton_11->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::SystemShutdown));
        toolButton_11->setIcon(icon);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 50, 141, 121));
        label_2->setStyleSheet(QString::fromUtf8("background-color:transparent"));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../logo-abir.jpeg-removebg-preview.png")));
        label_2->setScaledContents(true);
        tabWidget = new QTabWidget(projet);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(230, 10, 811, 621));
        tabWidget->setStyleSheet(QString::fromUtf8("QMainWindow, QWidget {\n"
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
        tab = new QWidget();
        tab->setObjectName("tab");
        comboBox_4 = new QComboBox(tab);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(390, 130, 151, 26));
        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(250, 220, 551, 271));
        widget_2->setStyleSheet(QString::fromUtf8("background-color:rgb(248,200,220);"));
        tableWidget_2 = new QTableWidget(widget_2);
        if (tableWidget_2->columnCount() < 6)
            tableWidget_2->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget_2->rowCount() < 5)
            tableWidget_2->setRowCount(5);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(10, 20, 531, 231));
        tableWidget_2->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(280, 270, 21, 31));
        label_4->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_4->setPixmap(QPixmap(QString::fromUtf8("../delete_78dp_0000F5_FILL0_wght400_GRAD0_opsz48.png")));
        label_4->setScaledContents(true);
        label_8 = new QLabel(widget_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(300, 270, 21, 31));
        label_8->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
""));
        label_8->setPixmap(QPixmap(QString::fromUtf8("../pencil.png")));
        label_8->setScaledContents(true);
        label_20 = new QLabel(widget_2);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(280, 340, 21, 31));
        label_20->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_20->setPixmap(QPixmap(QString::fromUtf8("../delete_78dp_0000F5_FILL0_wght400_GRAD0_opsz48.png")));
        label_20->setScaledContents(true);
        label_21 = new QLabel(widget_2);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(300, 340, 21, 31));
        label_21->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
""));
        label_21->setPixmap(QPixmap(QString::fromUtf8("../pencil.png")));
        label_21->setScaledContents(true);
        label_22 = new QLabel(widget_2);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(300, 310, 21, 31));
        label_22->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
""));
        label_22->setPixmap(QPixmap(QString::fromUtf8("../pencil.png")));
        label_22->setScaledContents(true);
        label_23 = new QLabel(widget_2);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(280, 310, 21, 31));
        label_23->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_23->setPixmap(QPixmap(QString::fromUtf8("../delete_78dp_0000F5_FILL0_wght400_GRAD0_opsz48.png")));
        label_23->setScaledContents(true);
        label_24 = new QLabel(widget_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(280, 380, 21, 31));
        label_24->setStyleSheet(QString::fromUtf8("background-color: transparent"));
        label_24->setPixmap(QPixmap(QString::fromUtf8("../delete_78dp_0000F5_FILL0_wght400_GRAD0_opsz48.png")));
        label_24->setScaledContents(true);
        label_25 = new QLabel(widget_2);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(300, 380, 21, 31));
        label_25->setStyleSheet(QString::fromUtf8("background-color: transparent\n"
""));
        label_25->setPixmap(QPixmap(QString::fromUtf8("../pencil.png")));
        label_25->setScaledContents(true);
        lineEdit_4 = new QLineEdit(tab);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(250, 40, 171, 26));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(0, 10, 241, 541));
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
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 40, 63, 20));
        label_11->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 90, 81, 31));
        label_12->setStyleSheet(QString::fromUtf8("background:transparent;\n"
""));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 160, 101, 31));
        label_13->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 360, 81, 31));
        label_14->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 230, 91, 31));
        label_15->setStyleSheet(QString::fromUtf8("background:transparent;"));
        comboBox_5 = new QComboBox(groupBox_3);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName("comboBox_5");
        comboBox_5->setGeometry(QRect(10, 130, 161, 26));
        comboBox_6 = new QComboBox(groupBox_3);
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->setObjectName("comboBox_6");
        comboBox_6->setGeometry(QRect(10, 390, 161, 26));
        comboBox_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 300, 91, 31));
        label_16->setStyleSheet(QString::fromUtf8("background:transparent;\n"
""));
        toolButton_15 = new QToolButton(groupBox_3);
        toolButton_15->setObjectName("toolButton_15");
        toolButton_15->setGeometry(QRect(0, 480, 101, 41));
        toolButton_15->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_16 = new QToolButton(groupBox_3);
        toolButton_16->setObjectName("toolButton_16");
        toolButton_16->setGeometry(QRect(120, 480, 101, 41));
        toolButton_16->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        lineEdit_5 = new QLineEdit(groupBox_3);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(10, 70, 161, 26));
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit_3 = new QDateEdit(groupBox_3);
        dateEdit_3->setObjectName("dateEdit_3");
        dateEdit_3->setGeometry(QRect(10, 200, 161, 26));
        dateEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit_4 = new QDateEdit(groupBox_3);
        dateEdit_4->setObjectName("dateEdit_4");
        dateEdit_4->setGeometry(QRect(10, 270, 161, 26));
        dateEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_6 = new QLineEdit(groupBox_3);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(10, 330, 161, 26));
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_17 = new QLabel(tab);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(260, 130, 91, 31));
        toolButton_17 = new QToolButton(tab);
        toolButton_17->setObjectName("toolButton_17");
        toolButton_17->setGeometry(QRect(440, 30, 51, 51));
        toolButton_17->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        toolButton_17->setIcon(icon1);
        toolButton_17->setIconSize(QSize(30, 30));
        toolButton_18 = new QToolButton(tab);
        toolButton_18->setObjectName("toolButton_18");
        toolButton_18->setGeometry(QRect(260, 500, 201, 41));
        toolButton_18->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_19 = new QToolButton(tab);
        toolButton_19->setObjectName("toolButton_19");
        toolButton_19->setGeometry(QRect(520, 30, 121, 61));
        toolButton_19->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_20 = new QToolButton(tab);
        toolButton_20->setObjectName("toolButton_20");
        toolButton_20->setGeometry(QRect(820, 310, 71, 51));
        toolButton_20->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        toolButton_20->setIcon(icon2);
        toolButton_20->setIconSize(QSize(30, 30));
        toolButton_21 = new QToolButton(tab);
        toolButton_21->setObjectName("toolButton_21");
        toolButton_21->setGeometry(QRect(820, 240, 71, 51));
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
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        toolButton_21->setIcon(icon3);
        toolButton_21->setIconSize(QSize(30, 30));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        groupBox_statistics = new QGroupBox(tab_2);
        groupBox_statistics->setObjectName("groupBox_statistics");
        groupBox_statistics->setGeometry(QRect(20, 0, 761, 541));
        groupBox_statistics->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #F5F5F5,\n"
"                                stop:1 #E8E8E8);\n"
"    color: #333333;\n"
"    font-weight: bold;\n"
"    padding: 15px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top centre;\n"
"    padding: 10px 20px;\n"
"    border-radius: 15px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"    color: white;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"}"));
        label_period_title = new QLabel(groupBox_statistics);
        label_period_title->setObjectName("label_period_title");
        label_period_title->setGeometry(QRect(30, 50, 141, 51));
        label_period_title->setStyleSheet(QString::fromUtf8("background : transparent;"));
        comboBox_period = new QComboBox(groupBox_statistics);
        comboBox_period->addItem(QString());
        comboBox_period->addItem(QString());
        comboBox_period->addItem(QString());
        comboBox_period->addItem(QString());
        comboBox_period->setObjectName("comboBox_period");
        comboBox_period->setGeometry(QRect(180, 50, 181, 51));
        comboBox_period->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 10px;\n"
"    padding: 5px;\n"
"    background-color: white;\n"
"    font-size: 11pt;\n"
"}\n"
"QComboBox:hover {\n"
"    border-color: #BDC3C7;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"}"));
        label_summary_title = new QLabel(groupBox_statistics);
        label_summary_title->setObjectName("label_summary_title");
        label_summary_title->setGeometry(QRect(30, 130, 281, 41));
        label_summary_title->setStyleSheet(QString::fromUtf8("background : transparent;"));
        frame_broadcast = new QFrame(groupBox_statistics);
        frame_broadcast->setObjectName("frame_broadcast");
        frame_broadcast->setGeometry(QRect(30, 210, 151, 291));
        frame_broadcast->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #E8F5E8;\n"
"    border: 2px solid #4CAF50;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"}"));
        frame_broadcast->setFrameShape(QFrame::Shape::StyledPanel);
        verticalLayout = new QVBoxLayout(frame_broadcast);
        verticalLayout->setObjectName("verticalLayout");
        label_broadcast_title = new QLabel(frame_broadcast);
        label_broadcast_title->setObjectName("label_broadcast_title");

        verticalLayout->addWidget(label_broadcast_title);

        label_broadcast_count = new QLabel(frame_broadcast);
        label_broadcast_count->setObjectName("label_broadcast_count");

        verticalLayout->addWidget(label_broadcast_count);

        label_broadcast_subtitle = new QLabel(frame_broadcast);
        label_broadcast_subtitle->setObjectName("label_broadcast_subtitle");

        verticalLayout->addWidget(label_broadcast_subtitle);

        frame_live = new QFrame(groupBox_statistics);
        frame_live->setObjectName("frame_live");
        frame_live->setGeometry(QRect(190, 210, 151, 291));
        frame_live->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #FFF3E0;\n"
"    border: 2px solid #FF9800;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"}"));
        frame_live->setFrameShape(QFrame::Shape::StyledPanel);
        verticalLayout_2 = new QVBoxLayout(frame_live);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_live_title = new QLabel(frame_live);
        label_live_title->setObjectName("label_live_title");

        verticalLayout_2->addWidget(label_live_title);

        label_live_count = new QLabel(frame_live);
        label_live_count->setObjectName("label_live_count");

        verticalLayout_2->addWidget(label_live_count);

        label_live_subtitle = new QLabel(frame_live);
        label_live_subtitle->setObjectName("label_live_subtitle");

        verticalLayout_2->addWidget(label_live_subtitle);

        frame_youtube = new QFrame(groupBox_statistics);
        frame_youtube->setObjectName("frame_youtube");
        frame_youtube->setGeometry(QRect(360, 210, 161, 291));
        frame_youtube->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #FFEBEE;\n"
"    border: 2px solid #F44336;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"}"));
        frame_youtube->setFrameShape(QFrame::Shape::StyledPanel);
        verticalLayout_3 = new QVBoxLayout(frame_youtube);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_youtube_title = new QLabel(frame_youtube);
        label_youtube_title->setObjectName("label_youtube_title");

        verticalLayout_3->addWidget(label_youtube_title);

        label_youtube_count = new QLabel(frame_youtube);
        label_youtube_count->setObjectName("label_youtube_count");

        verticalLayout_3->addWidget(label_youtube_count);

        label_youtube_subtitle = new QLabel(frame_youtube);
        label_youtube_subtitle->setObjectName("label_youtube_subtitle");

        verticalLayout_3->addWidget(label_youtube_subtitle);

        frame_total = new QFrame(groupBox_statistics);
        frame_total->setObjectName("frame_total");
        frame_total->setGeometry(QRect(540, 210, 181, 291));
        frame_total->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #F3E5F5;\n"
"    border: 2px solid #9C27B0;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"}"));
        frame_total->setFrameShape(QFrame::Shape::StyledPanel);
        verticalLayout_4 = new QVBoxLayout(frame_total);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_total_title = new QLabel(frame_total);
        label_total_title->setObjectName("label_total_title");

        verticalLayout_4->addWidget(label_total_title);

        label_total_count = new QLabel(frame_total);
        label_total_count->setObjectName("label_total_count");

        verticalLayout_4->addWidget(label_total_count);

        label_total_subtitle = new QLabel(frame_total);
        label_total_subtitle->setObjectName("label_total_subtitle");

        verticalLayout_4->addWidget(label_total_subtitle);

        tabWidget->addTab(tab_2, QString());
        stackedWidget->addWidget(projet);
        sponsor = new QWidget();
        sponsor->setObjectName("sponsor");
        groupBox_2 = new QGroupBox(sponsor);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 20, 211, 611));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        toolButton_7 = new QToolButton(groupBox_2);
        toolButton_7->setObjectName("toolButton_7");
        toolButton_7->setGeometry(QRect(20, 170, 171, 51));
        toolButton_7->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_8 = new QToolButton(groupBox_2);
        toolButton_8->setObjectName("toolButton_8");
        toolButton_8->setGeometry(QRect(20, 430, 171, 51));
        toolButton_8->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_9 = new QToolButton(groupBox_2);
        toolButton_9->setObjectName("toolButton_9");
        toolButton_9->setGeometry(QRect(20, 360, 161, 51));
        toolButton_9->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_10 = new QToolButton(groupBox_2);
        toolButton_10->setObjectName("toolButton_10");
        toolButton_10->setGeometry(QRect(20, 290, 171, 51));
        toolButton_10->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_12 = new QToolButton(groupBox_2);
        toolButton_12->setObjectName("toolButton_12");
        toolButton_12->setGeometry(QRect(20, 230, 171, 51));
        toolButton_12->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_13 = new QToolButton(groupBox_2);
        toolButton_13->setObjectName("toolButton_13");
        toolButton_13->setGeometry(QRect(20, 490, 171, 51));
        toolButton_13->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_14 = new QToolButton(groupBox_2);
        toolButton_14->setObjectName("toolButton_14");
        toolButton_14->setGeometry(QRect(70, 550, 61, 51));
        toolButton_14->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        toolButton_14->setIcon(icon);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 50, 141, 121));
        label_3->setStyleSheet(QString::fromUtf8("background-color:transparent"));
        label_3->setPixmap(QPixmap(QString::fromUtf8("../logo-abir.jpeg-removebg-preview.png")));
        label_3->setScaledContents(true);
        tabWidget_2 = new QTabWidget(sponsor);
        tabWidget_2->setObjectName("tabWidget_2");
        tabWidget_2->setGeometry(QRect(240, 20, 951, 631));
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
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(0, 0, 291, 541));
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
"}QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 2"
                        "0px;\n"
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
"}QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1"
                        ":0,\n"
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
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 60, 63, 20));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background:transparent;"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(30, 130, 63, 20));
        label_10->setStyleSheet(QString::fromUtf8("background:transparent;\n"
""));
        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(30, 200, 111, 20));
        label_18->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background:transparent;"));
        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(30, 270, 111, 20));
        label_19->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background:transparent;"));
        comboBox_2 = new QComboBox(groupBox_4);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(50, 230, 191, 28));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_26 = new QLabel(groupBox_4);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(30, 340, 111, 20));
        label_26->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background:transparent;"));
        dateEdit_5 = new QDateEdit(groupBox_4);
        dateEdit_5->setObjectName("dateEdit_5");
        dateEdit_5->setGeometry(QRect(50, 300, 191, 29));
        dateEdit_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit_6 = new QDateEdit(groupBox_4);
        dateEdit_6->setObjectName("dateEdit_6");
        dateEdit_6->setGeometry(QRect(50, 370, 191, 29));
        dateEdit_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_27 = new QLabel(groupBox_4);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(30, 410, 81, 20));
        label_27->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background:transparent;"));
        lineEdit_2 = new QLineEdit(groupBox_4);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(50, 440, 191, 28));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        toolButton_22 = new QToolButton(groupBox_4);
        toolButton_22->setObjectName("toolButton_22");
        toolButton_22->setGeometry(QRect(10, 480, 131, 51));
        toolButton_22->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        lineEdit_7 = new QLineEdit(groupBox_4);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(50, 90, 191, 28));
        lineEdit_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_8 = new QLineEdit(groupBox_4);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(50, 160, 191, 28));
        lineEdit_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        toolButton_23 = new QToolButton(groupBox_4);
        toolButton_23->setObjectName("toolButton_23");
        toolButton_23->setGeometry(QRect(150, 480, 111, 51));
        toolButton_23->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        lineEdit_9 = new QLineEdit(tab_3);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(300, 60, 201, 28));
        lineEdit_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_28 = new QLabel(tab_3);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(310, 20, 101, 31));
        comboBox_7 = new QComboBox(tab_3);
        comboBox_7->addItem(QString());
        comboBox_7->setObjectName("comboBox_7");
        comboBox_7->setGeometry(QRect(430, 20, 121, 31));
        comboBox_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        widget_3 = new QWidget(tab_3);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(300, 120, 541, 251));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 200, 220);"));
        tableWidget_3 = new QTableWidget(widget_3);
        if (tableWidget_3->columnCount() < 6)
            tableWidget_3->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        tableWidget_3->setObjectName("tableWidget_3");
        tableWidget_3->setGeometry(QRect(30, 30, 501, 211));
        tableWidget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        toolButton_24 = new QToolButton(tab_3);
        toolButton_24->setObjectName("toolButton_24");
        toolButton_24->setGeometry(QRect(860, 240, 61, 51));
        toolButton_24->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        toolButton_24->setIcon(icon3);
        toolButton_24->setIconSize(QSize(30, 30));
        toolButton_25 = new QToolButton(tab_3);
        toolButton_25->setObjectName("toolButton_25");
        toolButton_25->setGeometry(QRect(860, 180, 61, 51));
        toolButton_25->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
"}"));
        toolButton_25->setIcon(icon2);
        toolButton_25->setIconSize(QSize(30, 30));
        toolButton_26 = new QToolButton(tab_3);
        toolButton_26->setObjectName("toolButton_26");
        toolButton_26->setGeometry(QRect(520, 60, 61, 51));
        toolButton_26->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_26->setIcon(icon1);
        toolButton_26->setIconSize(QSize(30, 30));
        toolButton_27 = new QToolButton(tab_3);
        toolButton_27->setObjectName("toolButton_27");
        toolButton_27->setGeometry(QRect(600, 60, 131, 51));
        toolButton_27->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        groupBox_5 = new QGroupBox(tab_3);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(300, 390, 291, 71));
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        label_5 = new QLabel(tab_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(1100, 400, 71, 61));
        label_5->setPixmap(QPixmap(QString::fromUtf8("../../\342\200\224Pngtree\342\200\224alert notification bell 3d icon_8631570.png")));
        label_5->setScaledContents(true);
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        groupBox_6 = new QGroupBox(tab_4);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(30, 30, 611, 451));
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
"}QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 2"
                        "0px;\n"
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
"}QGroupBox {\n"
"    border: 2px solid #9B59B6;\n"
"    border-radius: 15px;\n"
"    margin-top: 20px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1"
                        ":0,\n"
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
        label_6 = new QLabel(groupBox_6);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(350, 80, 201, 271));
        label_6->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/Gemini_Generated_Image_7p40tj7p40tj7p40.png")));
        label_6->setScaledContents(true);
        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(50, 80, 231, 271));
        label_7->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/Gemini_Generated_Image_7immvh7immvh7imm.png")));
        label_7->setScaledContents(true);
        groupBox_7 = new QGroupBox(tab_4);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(670, 100, 221, 241));
        groupBox_7->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        toolButton_28 = new QToolButton(groupBox_7);
        toolButton_28->setObjectName("toolButton_28");
        toolButton_28->setGeometry(QRect(50, 150, 131, 51));
        toolButton_28->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        toolButton_29 = new QToolButton(groupBox_7);
        toolButton_29->setObjectName("toolButton_29");
        toolButton_29->setGeometry(QRect(50, 70, 131, 51));
        toolButton_29->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 1px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);}"));
        tabWidget_2->addTab(tab_4, QString());
        stackedWidget->addWidget(sponsor);
        integ_ray_rima->setCentralWidget(centralwidget);
        menubar = new QMenuBar(integ_ray_rima);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1301, 26));
        integ_ray_rima->setMenuBar(menubar);
        statusbar = new QStatusBar(integ_ray_rima);
        statusbar->setObjectName("statusbar");
        integ_ray_rima->setStatusBar(statusbar);

        retranslateUi(integ_ray_rima);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(integ_ray_rima);
    } // setupUi

    void retranslateUi(QMainWindow *integ_ray_rima)
    {
        integ_ray_rima->setWindowTitle(QCoreApplication::translate("integ_ray_rima", "integ_ray_rima", nullptr));
        groupBox->setTitle(QCoreApplication::translate("integ_ray_rima", " NeoCreate", nullptr));
        toolButton->setText(QCoreApplication::translate("integ_ray_rima", " Staff technique", nullptr));
        toolButton_2->setText(QCoreApplication::translate("integ_ray_rima", " Sponsor", nullptr));
        toolButton_3->setText(QCoreApplication::translate("integ_ray_rima", " Projet", nullptr));
        toolButton_4->setText(QCoreApplication::translate("integ_ray_rima", " Materiel", nullptr));
        toolButton_5->setText(QCoreApplication::translate("integ_ray_rima", " Client", nullptr));
        toolButton_6->setText(QCoreApplication::translate("integ_ray_rima", " Createur", nullptr));
        toolButton_11->setText(QCoreApplication::translate("integ_ray_rima", "...", nullptr));
        label_2->setText(QString());
        comboBox_4->setItemText(0, QCoreApplication::translate("integ_ray_rima", "date debut", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("integ_ray_rima", "date fin", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("integ_ray_rima", "montant", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("integ_ray_rima", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("integ_ray_rima", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("integ_ray_rima", "Date debut", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("integ_ray_rima", "Date Fin ", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("integ_ray_rima", "Montant", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("integ_ray_rima", "Paiment", nullptr));
        label_4->setText(QString());
        label_8->setText(QString());
        label_20->setText(QString());
        label_21->setText(QString());
        label_22->setText(QString());
        label_23->setText(QString());
        label_24->setText(QString());
        label_25->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("integ_ray_rima", "Projet", nullptr));
        label_11->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Id</span></p></body></html>", nullptr));
        label_12->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">  projet</span></p></body></html>", nullptr));
        label_13->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Date Debut</span></p></body></html>", nullptr));
        label_14->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Paiment</span></p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Date Fin</span></p></body></html>", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("integ_ray_rima", "podcast", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("integ_ray_rima", "live", nullptr));

        comboBox_6->setItemText(0, QCoreApplication::translate("integ_ray_rima", "cash", nullptr));
        comboBox_6->setItemText(1, QCoreApplication::translate("integ_ray_rima", "virement ", nullptr));

        label_16->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Montant</span></p></body></html>", nullptr));
        toolButton_15->setText(QCoreApplication::translate("integ_ray_rima", "annuler", nullptr));
        toolButton_16->setText(QCoreApplication::translate("integ_ray_rima", "Ajouter", nullptr));
        label_17->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Trier par:</span></p></body></html>", nullptr));
        toolButton_17->setText(QString());
        toolButton_18->setText(QCoreApplication::translate("integ_ray_rima", "exportation pdf", nullptr));
        toolButton_19->setText(QCoreApplication::translate("integ_ray_rima", "Afficher", nullptr));
        toolButton_20->setText(QCoreApplication::translate("integ_ray_rima", "...", nullptr));
        toolButton_21->setText(QCoreApplication::translate("integ_ray_rima", "...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("integ_ray_rima", " Acceuil", nullptr));
        groupBox_statistics->setTitle(QCoreApplication::translate("integ_ray_rima", "\360\237\223\212 Statistiques des Demandes Clients", nullptr));
        label_period_title->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#333333;\">\360\237\223\205 P\303\251riode:</span></p></body></html>", nullptr));
        comboBox_period->setItemText(0, QCoreApplication::translate("integ_ray_rima", "Cette Semaine", nullptr));
        comboBox_period->setItemText(1, QCoreApplication::translate("integ_ray_rima", "Ce Mois", nullptr));
        comboBox_period->setItemText(2, QCoreApplication::translate("integ_ray_rima", "Semaine Derni\303\250re", nullptr));
        comboBox_period->setItemText(3, QCoreApplication::translate("integ_ray_rima", "Mois Dernier", nullptr));

        label_summary_title->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#9B59B6;\">\360\237\222\274 R\303\251sum\303\251 des Services</span></p></body></html>", nullptr));
        label_broadcast_title->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:700; color:#4CAF50;\">\360\237\223\273 BROADCAST</span></p></body></html>", nullptr));
        label_broadcast_count->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:700; color:#4CAF50;\">0</span></p></body></html>", nullptr));
        label_broadcast_subtitle->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; color:#4CAF50;\">demandes</span></p></body></html>", nullptr));
        label_live_title->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:700; color:#ff9800;\">\360\237\224\264 LIVE </span></p></body></html>", nullptr));
        label_live_count->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:700; color:#FF9800;\">0</span></p></body></html>", nullptr));
        label_live_subtitle->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; color:#FF9800;\">demandes</span></p></body></html>", nullptr));
        label_youtube_title->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:700; color:#F44336;\">\360\237\216\254 YOUTUBE ADS</span></p></body></html>", nullptr));
        label_youtube_count->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:700; color:#F44336;\">0</span></p></body></html>", nullptr));
        label_youtube_subtitle->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; color:#F44336;\">demandes</span></p></body></html>", nullptr));
        label_total_title->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:700; color:#9C27B0;\">\360\237\223\212 TOTAL</span></p></body></html>", nullptr));
        label_total_count->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:700; color:#9C27B0;\">0</span></p></body></html>", nullptr));
        label_total_subtitle->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; color:#9C27B0;\">demandes</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("integ_ray_rima", "Statistiques", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("integ_ray_rima", " NeoCreate", nullptr));
        toolButton_7->setText(QCoreApplication::translate("integ_ray_rima", " Staff technique", nullptr));
        toolButton_8->setText(QCoreApplication::translate("integ_ray_rima", " Sponsor", nullptr));
        toolButton_9->setText(QCoreApplication::translate("integ_ray_rima", " Projet", nullptr));
        toolButton_10->setText(QCoreApplication::translate("integ_ray_rima", " Materiel", nullptr));
        toolButton_12->setText(QCoreApplication::translate("integ_ray_rima", " Client", nullptr));
        toolButton_13->setText(QCoreApplication::translate("integ_ray_rima", " Createur", nullptr));
        toolButton_14->setText(QCoreApplication::translate("integ_ray_rima", "...", nullptr));
        label_3->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("integ_ray_rima", "Ajouter Sponsor", nullptr));
        label_9->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Id:</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Nom:</span></p></body></html>", nullptr));
        label_18->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">contrubition:</span></p></body></html>", nullptr));
        label_19->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Date debut:</span></p></body></html>", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("integ_ray_rima", "Argent", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("integ_ray_rima", "Materiel", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("integ_ray_rima", "Service", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("integ_ray_rima", "Autre", nullptr));

        label_26->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Date Fin:</span></p></body></html>", nullptr));
        label_27->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Email:</span></p></body></html>", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("integ_ray_rima", "rimma118@gmail.com", nullptr));
        toolButton_22->setText(QCoreApplication::translate("integ_ray_rima", "Ajouter", nullptr));
        lineEdit_7->setText(QCoreApplication::translate("integ_ray_rima", "129108766", nullptr));
        lineEdit_8->setText(QCoreApplication::translate("integ_ray_rima", "RIMA", nullptr));
        toolButton_23->setText(QCoreApplication::translate("integ_ray_rima", "modifier", nullptr));
        label_28->setText(QCoreApplication::translate("integ_ray_rima", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700; color:#000000;\">Trier par:</span></p></body></html>", nullptr));
        comboBox_7->setItemText(0, QCoreApplication::translate("integ_ray_rima", "Contrubtion", nullptr));

        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("integ_ray_rima", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("integ_ray_rima", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("integ_ray_rima", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("integ_ray_rima", "Date debut", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("integ_ray_rima", "Date Fin", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_3->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("integ_ray_rima", "Email", nullptr));
        toolButton_24->setText(QCoreApplication::translate("integ_ray_rima", "...", nullptr));
        toolButton_25->setText(QCoreApplication::translate("integ_ray_rima", "...", nullptr));
        toolButton_26->setText(QCoreApplication::translate("integ_ray_rima", "...", nullptr));
        toolButton_27->setText(QCoreApplication::translate("integ_ray_rima", "Afficher", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("integ_ray_rima", "NOTIFICATIONS ET ALERTE", nullptr));
        label_5->setText(QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("integ_ray_rima", "Acceuil", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("integ_ray_rima", "Qtastiques de sponsors", nullptr));
        label_6->setText(QString());
        label_7->setText(QString());
        groupBox_7->setTitle(QString());
        toolButton_28->setText(QCoreApplication::translate("integ_ray_rima", "IA recomendation", nullptr));
        toolButton_29->setText(QCoreApplication::translate("integ_ray_rima", "Exportation pdf", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("integ_ray_rima", "Fonctionnalites", nullptr));
    } // retranslateUi

};

namespace Ui {
    class integ_ray_rima: public Ui_integ_ray_rima {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEG_RAY_RIMA_H
