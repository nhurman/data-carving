QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BitGrapher
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    core/bitstring.cpp \
    core/dump.cpp \
    core/dumpset.cpp \
    algorithms/diagonal.cpp \
    algorithms/similarities.cpp \
    encodings/encoding.cpp \
    ui/bitgrapharea.cpp \
    ui/dotplotview.cpp \
    ui/dumpcombobox.cpp \
    ui/dumpsettreewidget.cpp \
    ui/encodingsdialog.cpp \
    ui/mainwindow.cpp \
    ui/similaritesdialog.cpp

HEADERS  += \
    core/bitstring.h \
    core/dump.h \
    core/dumpset.h \
    algorithms/diagonal.h \
    algorithms/similarities.h \
    encodings/encoding.h \
    ui/bitgrapharea.h \
    ui/dotplotview.h \
    ui/dumpcombobox.h \
    ui/dumpsettreewidget.h \
    ui/encodingsdialog.h \
    ui/mainwindow.h \
    ui/similaritesdialog.h

FORMS    += \
    ui/encodingsdialog.ui \
    ui/mainwindow.ui \
