QT += core sql
QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = app

# 项目名称
TARGET = test_database

# 源文件
SOURCES += \
    test_database.cpp \
    databasemanager.cpp

# 头文件
HEADERS += \
    databasemanager.h

# 编译选项
DEFINES += QT_DEPRECATED_WARNINGS

# 输出目录
DESTDIR = $$PWD/bin 