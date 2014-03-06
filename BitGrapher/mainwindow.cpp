#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bitstring.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_bitstring = new BitString("615B5F1F58503C42454C56414E4445523C4D45554C454E3C3C4A4F53453C483C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C45463437383539373C3942454C383030313136324D313130333231383C3C3C3C3C3C3C3C3C3C3C3C3C3C3034");
    ui->plainTextEdit->appendPlainText(m_bitstring->toString().c_str());

    ui->graphArea->setBitString(m_bitstring);

    /* ---------------- TESTS -------------- */
    /*              To be moved              */

    if(m_bitstring->contains(BitString("B5F1")))
        std::cout << "yes" << std::endl;
    else
        std::cout << "no" << std::endl;

    BitString bitTest1("FF");
    std::cout << "Hamming Weight : " << bitTest1.hammingWeight() << std::endl;

    BitString bitTest2("F3");
    std::cout << "Hamming Distance : " << bitTest1.hammingDistance(bitTest2) << std::endl;



    /* ------------------------------------- */
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_bitstring;
}
