QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BitGrapher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bitgrapharea.cpp \
    bitstring.cpp \
    diagonal.cpp \
    dump.cpp \
    dumpset.cpp \
    dotplotview.cpp \
    dumpsettreewidget.cpp \
    encoding.cpp \
    similaritesdialog.cpp \
    encodingsdialog.cpp

HEADERS  += mainwindow.h \
    bitgrapharea.h \
    bitstring.h \
    diagonal.h \
    dump.h \
    dumpset.h \
    dotplotview.h \
    dumpsettreewidget.h \
    encoding.h \
    similaritesdialog.h \
    encodingsdialog.h

FORMS    += mainwindow.ui \
    encodingsdialog.ui
