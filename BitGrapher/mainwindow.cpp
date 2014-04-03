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

    //ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

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
    /*QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     DEFAULT_DIRECTORY,
                                                     tr("Files (*.*)"));
    m_dumpSet->addDump(fileName.toStdString());*/
    //ui->listWidget->addItem(fileName);

}

void MainWindow::on_actionSave_triggered()
{
    if(m_dumpSet != NULL)
    {
        if(m_dumpSet->hasName())
            m_dumpSet->save();
        else
            on_actionSave_as_triggered(); //save as instead
    }
    else
    {
        std::cout << "Unable to save dump : no dump selected" << std::endl ;
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    if(m_dumpSet != NULL)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save dump set as..."),
                                                         DEFAULT_DIRECTORY,
                                                         tr("Dump Sets (*.ds)"));
        if(m_dumpSet->saveToFile(fileName))
        {
            m_dumpSet->setFileName(fileName);
        }
    }
    else
    {
        std::cout << "Unable to save dump : no dump selected" << std::endl ;
    }
}
void MainWindow::on_actionDiagonals_View_triggered(){
    std::cout << "Diagonals !" << std::endl ;
}
void MainWindow::on_actionBitmap_View_triggered() {
    std::cout << "Bitmap !" << std::endl ;
}


/*void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    m_bitstring = m_dumpSet.find(current->text().toStdString())->getBitString();
    refreshDisplay();
}*/

void MainWindow::refreshDisplay()
{
    if(m_bitstring != NULL)
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
    else
    {
        std::cout<<"Dump introuvable dans le set courant."<<std::endl;
    }
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current->parent() == NULL) //if a dumpset was selected
    {
        m_dumpSet = DumpSet::m_openedDumpSets[current->text(0)];
        std::cout<<"toplevel"<<std::endl;
    }
    else //if a dump is selected
    {
        if(current->parent() != previous->parent() || current->parent() != previous) //if the dumpset has changed
        {
            m_dumpSet = DumpSet::m_openedDumpSets[current->parent()->text(0)];
            std::cout<<"new parent"<<std::endl;
        }
        m_bitstring = m_dumpSet->find(current->text(0))->getBitString();
        std::cout<<"lowlevel"<<std::endl;
    }
    refreshDisplay();
}

void MainWindow::on_actionAdd_Dump_to_Set_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open dump file"),
                                                     DEFAULT_DIRECTORY,
                                                     tr("Files (*.*)"));
    ui->treeWidget->setCurrentItem(m_dumpSet->addDump(fileName));
}

void MainWindow::on_actionNew_Dump_Set_triggered()
{
    QString name = "NewDumpSet_" + QString::number(DumpSet::m_nbNewDumpSets++);
    QTreeWidgetItem* i = new QTreeWidgetItem(QStringList(name));
    DumpSet::m_openedDumpSets[name] = new DumpSet(i);
    ui->treeWidget->addTopLevelItem(i);
    ui->treeWidget->setCurrentItem(i);
}
