QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BitGrapher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bitgrapharea.cpp \
    bitstring.cpp

HEADERS  += mainwindow.h \
    bitgrapharea.h \
    bitstring.h

FORMS    += mainwindow.ui
