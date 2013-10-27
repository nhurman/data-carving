#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bitstring.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_bitstring = new BitString("615B5F1F58503C42454C56414E4445523C4D45554C454E3C3C4A4F53453C483C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C45463437383539373C3942454C383030313136324D313130333231383C3C3C3C3C3C3C3C3C3C3C3C3C3C3034");
    ui->plainTextEdit->appendPlainText(m_bitstring->toString().c_str());

    ui->graphArea->setBitString(m_bitstring);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_bitstring;
}
