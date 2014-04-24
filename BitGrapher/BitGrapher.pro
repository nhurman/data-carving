QT       += core gui widgets
QMAKE_CXXFLAGS += -std=c++11

TARGET = BitGrapher
TEMPLATE = app

SOURCES += \
  main.cpp \
  ui/MainWindow.cpp \
    core/BitString.cpp \
    core/DumpSet.cpp \
    core/Dump.cpp \
    core/Exception.cpp \
    ui/DumpSetTreeWidget.cpp \
    ui/BitmapWidget.cpp \
    ui/HexViewWidget.cpp \
    encoding/Hexadecimal.cpp \
    encoding/Encoding.cpp \
    encoding/ASCII.cpp \
    ui/TextViewWidget.cpp \
    ui/ViewWidget.cpp

HEADERS  += \
  ui/MainWindow.h \
    core/BitString.h \
    core/DumpSet.h \
    core/Dump.h \
    core/Exception.h \
    ui/DumpSetTreeWidget.h \
    ui/BitmapWidget.h \
    ui/HexViewWidget.h \
    encoding/ASCII.h \
    encoding/Hexadecimal.h \
    encoding/Encoding.h \
    ui/TextViewWidget.h \
    ui/ViewWidget.h

FORMS    += \
  ui/MainWindow.ui
