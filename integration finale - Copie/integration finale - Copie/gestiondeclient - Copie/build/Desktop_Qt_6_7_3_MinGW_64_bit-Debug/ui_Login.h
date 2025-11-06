/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *widget;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *id;
    QLineEdit *mdp;
    QLabel *label_3;
    QPushButton *connect;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QLabel *label_4;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(1167, 590);
        widget = new QWidget(Login);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(-20, -10, 1191, 611));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(189, 195, 199);"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(450, 120, 371, 341));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 60, 91, 21));
        label->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 160, 111, 21));
        label_2->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        id = new QLineEdit(groupBox);
        id->setObjectName("id");
        id->setGeometry(QRect(70, 101, 161, 31));
        id->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color:black;"));
        mdp = new QLineEdit(groupBox);
        mdp->setObjectName("mdp");
        mdp->setGeometry(QRect(70, 200, 161, 31));
        mdp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color:black;"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(230, 310, 121, 16));
        label_3->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        connect = new QPushButton(groupBox);
        connect->setObjectName("connect");
        connect->setGeometry(QRect(130, 260, 111, 41));
        connect->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 1px;\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #9B59B6,\n"
"                                stop:1 #BDC3C7);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(spread:pad,\n"
"                                x1:0, y1:0,\n"
"                                x2:1, y2:0,\n"
"                                stop:0 #BDC3C7,\n"
"                                stop:1 #F8C8DC);\n"
"}\n"
""));
        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(30, 100, 41, 31));
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
"}"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ContactNew));
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(30, 30));
        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(30, 200, 41, 31));
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
"}"));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::SystemLockScreen));
        toolButton_2->setIcon(icon1);
        toolButton_2->setIconSize(QSize(30, 30));
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(140, 30, 111, 91));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/logo..jpeg")));
        label_4->setScaledContents(true);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Login", "Connexion", nullptr));
        label->setText(QCoreApplication::translate("Login", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">Id unique</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#000000;\">Mot de passe</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "<html><head/><body><p><span style=\" font-weight:700; color:#ff0000;\">Mot de passe oubli\303\251?</span></p></body></html>", nullptr));
        connect->setText(QCoreApplication::translate("Login", "Se connecter", nullptr));
        toolButton->setText(QCoreApplication::translate("Login", "...", nullptr));
        toolButton_2->setText(QCoreApplication::translate("Login", "...", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
