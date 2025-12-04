QT       += core gui sql printsupport
QT += charts
QT += core gui widgets network sql
QT += core gui sql network

QT += printsupport
QT += core gui network
# Pour inclure le dossier SimpleMail
INCLUDEPATH += $$PWD/SimpleMail



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appdesign.cpp \
    client.cpp \
    connection.cpp \
    gestioncreateur.cpp \
    main.cpp \
    Login.cpp\
    mainwindow.cpp \
    projet.cpp \
    staff.cpp \
    materiel.cpp \
    sponsor.cpp \
    sponsormanager.cpp \
    chatwindow.cpp \
    geminimanager.cpp \

HEADERS += \
    appdesign.h \
    client.h \
    connection.h \
    Login.h\
    gestioncreateur.h \
    mainwindow.h \
    projet.h \
    staff.h \
    materiel.h \
    sponsor.h \
    sponsormanager.h \
    chatwindow.h \
    geminimanager.h \

FORMS += \
    Login.ui\
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
