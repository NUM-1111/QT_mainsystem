QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = test_user_management
TEMPLATE = app

SOURCES += \
    databasemanager.cpp \
    groupmanager.cpp \
    groupmanagerdialog.cpp \
    logindialog.cpp \
    permissionmanager.cpp \
    registerdialog.cpp \
    usermanager.cpp \
    usermanagerdialog.cpp \
    test_user_management.cpp

HEADERS += \
    config.h \
    databasemanager.h \
    groupmanager.h \
    groupmanagerdialog.h \
    logindialog.h \
    permissionmanager.h \
    registerdialog.h \
    struct.h \
    usermanager.h \
    usermanagerdialog.h

FORMS += \
    groupmanagerdialog.ui \
    logindialog.ui \
    registerdialog.ui \
    usermanagerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target 