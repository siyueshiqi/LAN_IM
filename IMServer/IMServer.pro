#-------------------------------------------------
#
# Project created by QtCreator 2014-03-14T17:26:27
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = IMServer
TEMPLATE = app


SOURCES += main.cpp\
        view/IMServerWindow.cpp \
    control/IMServerMessageCtrl.cpp \
    model/IMTcpServer.cpp \
    model/IMThread.cpp \
    control/IMDatabaseCtrl.cpp \
    model/IMUser.cpp \
    control/IMClientSocketCtrl.cpp

HEADERS  += view/IMServerWindow.h \
    control/IMServerMessageCtrl.h \
    model/IMTcpServer.h \
    model/IMThread.h \
    control/IMDatabaseCtrl.h \
    model/IMUser.h \
    control/IMClientSocketCtrl.h \
    model/IMEncryption.h \
    model/IMConstant.h
