#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bitstring.h"
#include <iostream>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    m_bitstring = new BitString("615B5F1F58503C42454C56414E4445523C4D45554C454E3C3C4A4F53453C483C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C45463437383539373C3942454C383030313136324D313130333231383C3C3C3C3C3C3C3C3C3C3C3C3C3C3034");
    BitString bs("F15B5F1F58503C42454C56414E4445523C4D45554C454E3C3C4A4F53453C483C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C45463437383539373C3942454C383030313136324D313130333231383C3C3C3C3C3C3C3C3C3C3C3C3C3C3034");
    m_bitstring->bitOr(bs);
    ui->plainTextEdit->appendPlainText(m_bitstring->toString().c_str());
    ui->graphArea->setBitString(m_bitstring);

    /* ---------------- TESTS -------------- */
    /*              To be moved              */

    if(m_bitstring->contains(BitString("B5F1")))
        std::cout << "yes" << std::endl;
    else
        std::cout << "no" << std::endl;

    BitString bitTest1("615");
    std::cout << "Hamming Weight : " << bitTest1.hammingWeight() << std::endl;
    std::cout << "Hamming Weight (bit 0 to 8) : " << bitTest1.hammingWeight(0, 8) << std::endl;
    std::cout << "Hamming Weight (bit 2 to 5) : " << bitTest1.hammingWeight(2, 3) << std::endl;
    BitString bitTest2("F3");

    std::cout << "Hamming Distance : " << bitTest1.hammingDistance(bitTest2) << std::endl;


    BitString testDiag1("FFF0F0F000");
    BitString testDiag2("0F0F0F0FFF");
    Diagonal test(2,6,11);
    std::cout << "Diag test :" << test.toString() << std::endl ;
    std::list<Diagonal> listdiag = testDiag1.dotPlotPattern(testDiag2);
    std::cout << "Dotplot Pattern : " << listdiag.size() << std::endl;
    for (std::list<Diagonal>::iterator i = listdiag.begin(); i != listdiag.end(); i++ ){
        std::cout << "Diag " << (*i).toString() << std::endl ;
    }


    /* ------------------------------------- */
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_bitstring;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     DEFAULT_DIRECTORY,
                                                     tr("Files (*.*)"));
    m_dumpSet.addDump(fileName.toStdString());
    ui->listWidget->addItem(fileName);

}

void MainWindow::on_actionSave_triggered() {
    std::cout << "Saving !" << std::endl ;
}

void MainWindow::on_actionSave_as_triggered() {
    std::cout << "Saving as ... !" << std::endl ;
}
void MainWindow::on_actionDiagonals_View_triggered() {
    std::cout << "Saving as ... !" << std::endl ;
}
void MainWindow::on_actionBitmap_View_triggered() {
    std::cout << "Saving as ... !" << std::endl ;
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    m_bitstring = m_dumpSet.find(current->text().toStdString())->getBitString();
    refreshDisplay();
}

void MainWindow::refreshDisplay()
{
    //gets rid of old text
    ui->plainTextEdit->clear();
    //sets new text and image
    ui->plainTextEdit->appendPlainText(m_bitstring->toString().c_str());
    ui->graphArea->setBitString(m_bitstring);
    //refreshes the modifies fields
    ui->plainTextEdit->repaint();
    ui->graphArea->repaint();
}
