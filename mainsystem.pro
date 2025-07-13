QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasemanager.cpp \
    groupmanager.cpp \
    groupmanagerdialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    permissionmanager.cpp \
    registerdialog.cpp \
    subsystemclient.cpp \
    usermanager.cpp \
    usermanagerdialog.cpp

HEADERS += \
    config.h \
    databasemanager.h \
    groupmanager.h \
    groupmanagerdialog.h \
    logindialog.h \
    mainwindow.h \
    permissionmanager.h \
    registerdialog.h \
    struct.h \
    subsystemclient.h \
    usermanager.h \
    usermanagerdialog.h

FORMS += \
    groupmanagerdialog.ui \
    logindialog.ui \
    mainwindow.ui \
    registerdialog.ui \
    usermanagerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
