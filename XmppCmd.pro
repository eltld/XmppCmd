#-------------------------------------------------
#
# Project created by QtCreator 2014-04-11T10:51:33
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

include(qxmpp/qxmpp.pri)

TARGET = XmppCmd
CONFIG   += console

TEMPLATE = app

DESTDIR       = ../XmppCmd/bin
INSTALLS += target

SOURCES += main.cpp \
    Input.cpp \
    SystemConfig.cpp \
    XmppTransport.cpp \
    SystemConsole.cpp \
    SystemEngine.cpp

HEADERS += \
    Input.hpp \
    SystemConfig.hpp \
    DataStructures/TransportInfo.hpp \
    XmppTransport.hpp \
    SystemConsole.hpp \
    SystemEngine.hpp \
    DataStructures/ProxyInfo.hpp
