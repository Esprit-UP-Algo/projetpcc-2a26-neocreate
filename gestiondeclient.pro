QT += core gui sql printsupport widgets
QT += printsupport
QT += core network widgets
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Login.cpp \
    arduino.cpp \
    chatwindow.cpp \
    client.cpp \
    connection.cpp \
    geminimanager.cpp \
    gestioncreateur.cpp \
    main.cpp \
    mainwindow.cpp \
    materiel.cpp \
    projet.cpp \
    sponsor.cpp \
    sponsormanager.cpp \
    staff.cpp \
    staffsql.cpp

HEADERS += \
    Login.h \
    arduino.h \
    chatwindow.h \
    client.h \
    connection.h \
    geminimanager.h \
    gestioncreateur.h \
    mainwindow.h \
    materiel.h \
    projet.h \
    sponsor.h \
    sponsormanager.h \
    staff.h \
    staffsql.h

FORMS += \
    Login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    mmm.qrc

DISTFILES +=
