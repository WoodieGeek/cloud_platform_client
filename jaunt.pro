#-------------------------------------------------
#
# Project created by QtCreator 2020-04-18T12:57:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jaunt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    library/graph.cpp \
    library/node.cpp \
    library/edge.cpp \
    library/menu.cpp \
    library/data_adapter.cpp \
    library/json_edit.cpp \
    library/create_dialog.cpp \
    library/http_client/http_request.cpp \
    library/http_client/http_reply.cpp \
    library/http_client/http_manager.cpp

HEADERS += \
        mainwindow.h \
    library/graph.h \
    library/node.h \
    library/edge.h \
    library/menu.h \
    library/data_adapter.h \
    library/json_edit.h \
    library/create_dialog.h \
    library/http_client/http_request.h \
    library/http_client/http_reply.h \
    library/http_client/http_manager.h

FORMS += \
        mainwindow.ui
