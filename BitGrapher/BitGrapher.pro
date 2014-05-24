QT       += core gui widgets
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    ui/ViewWidget.cpp \
    encoding/Sixbit.cpp \
    ui/AssociationViewWidget.cpp \
    ui/DotPlotView.cpp \
    algorithms/Diagonal.cpp \
    algorithms/DotPlotPattern.cpp \
    ui/DiagonalViewItem.cpp \
    ui/DumpComboBox.cpp \
    ui/DotPlotDialog.cpp \
    algorithms/DotPlotResult.cpp \
    algorithms/Similarities.cpp

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
    ui/ViewWidget.h \
    encoding/Sixbit.h \
    ui/AssociationViewWidget.h \
    ui/DotPlotView.h \
    algorithms/Diagonal.h \
    algorithms/DotPlotPattern.h \
    ui/DiagonalViewItem.h \
    ui/DumpComboBox.h \
    ui/DotPlotDialog.h \
    algorithms/DotPlotResult.h \
    algorithms/Similarities.h

FORMS    += \
  ui/MainWindow.ui \
    ui/DotPlotView.ui
