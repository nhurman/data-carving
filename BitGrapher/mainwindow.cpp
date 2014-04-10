#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bitstring.h"
#include "similaritesdialog.h"
#include <iostream>

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    m_dumpSet = NULL;
    m_bitstring = new BitString("615B5F1F");//58503C42454C56414E4445523C4D45554C454E3C3C4A4F53453C483C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C45463437383539373C3942454C383030313136324D313130333231383C3C3C3C3C3C3C3C3C3C3C3C3C3C3034");
    BitString bs("F15B5F1F58503C42454C56414E4445523C4D45554C454E3C3C4A4F53453C483C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C45463437383539373C3942454C383030313136324D313130333231383C3C3C3C3C3C3C3C3C3C3C3C3C3C3034");
    m_bitstring->bitOr(bs);
    ui->textEdit->setText(m_bitstring->toString().c_str());
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

    std::cout << Encoding::toASCII(65 << 0) << std::endl;
    BitString testEncode("48414c50");
    std::cout << testEncode.toString() << " " <<  (unsigned int)(testEncode.getByte(17))<< std::endl;
    std::cout << Encoding::encode(testEncode, Encoding::toASCII, 0, 0, 8) << std::endl;
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
                                                     tr("Dump Sets (*.ds)"));
    ui->treeWidget->addDumpSet(new DumpSet(fileName));

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
            ui->treeWidget->changeDumpSetName(fileName);
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

void MainWindow::refreshDisplay()
{
    if(m_bitstring != NULL)
    {
        //gets rid of old text
        ui->textEdit->clear();
        //sets new text and image
        ui->textEdit->setText(m_bitstring->toString().c_str());
        ui->graphArea->setBitString(m_bitstring);
        //refreshes the modifies fields
        ui->textEdit->repaint();
        ui->graphArea->repaint();
    }
    else
    {
        std::cout<<"Dump introuvable dans le set courant."<<std::endl;
    }
}


void MainWindow::on_actionAdd_Dump_to_Set_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open dump file"),
                                                     DEFAULT_DIRECTORY,
                                                     tr("Files (*.*)"));
    if(fileName.size() > 0)
        ui->treeWidget->addDump(Dump(fileName));
}

void MainWindow::on_actionNew_Dump_Set_triggered()
{
    ui->treeWidget->addDumpSet(new DumpSet());
}

void MainWindow::on_treeWidget_selectedDumpChanged(Dump d)
{
    m_bitstring = d.getBitString();
    refreshDisplay();
}

void MainWindow::on_treeWidget_selectedDumpSetChanged(DumpSet* ds)
{
    m_dumpSet = ds;
}

void MainWindow::on_actionClose_triggered()
{
    ui->treeWidget->closeDumpSet();
}

void MainWindow::on_actionSimilarities_triggered()
{
    if(m_dumpSet == NULL) //no dump selected
    {
        QMessageBox::information(this, "Could not perform operation",
                                 "Please select a dump in a dump set.",
                                 QMessageBox::Ok);
        return;
    }

    std::vector<QString> dumpsVect = m_dumpSet->getDumpNames();
    QStringList dumps;
    for(unsigned int i = 0; i < dumpsVect.size(); i++)
    {
        dumps.push_back(dumpsVect.at(i));
    }
    dumps.removeOne(ui->treeWidget->getCurrentDump().getShortName());
    if(dumps.size() < 1) //no dump to compare to
    {
        QMessageBox::information(this, "Could not perform operation",
                                 "Not enough dumps in the dump set (at least 2 necessary)",
                                 QMessageBox::Ok);
        return;
    }
    /*
    bool ok;
    QString dump = QInputDialog::getItem(this, "Select dump to compare to", "Reference dump : ", dumps, 0, false, &ok);
    if(!ok) //cancel btton was pressed
        return;

    std::list<std::pair<int,int> > sim = BitString::similarities(*m_bitstring, *(m_dumpSet->find(dump)->getBitString()));
    */
    std::list<std::pair<int,int> >* sim = SimilaritesDialog::getSimilarities(m_dumpSet);
    if(sim == NULL) //cancel was pressed
        return;

    QString bitString = QString::fromStdString(m_bitstring->toString());
    ui->textEdit->clear();
    QString partOfText;
    int pos = 0;
    for (std::list<std::pair<int,int> >::iterator i = sim->begin(); i != sim->end(); i++ )
    {
        int length = BitString::convertCoords(i->first)-pos;
        partOfText = bitString.mid(pos,length); //text until next highlight
        ui->textEdit->setTextColor( QColor( "black" ) );
        ui->textEdit->insertPlainText(partOfText);

        pos = BitString::convertCoords(i->first);
        length = BitString::convertCoords(i->second) - pos + 1;
        partOfText = bitString.mid(pos, length); //highlighted text
        ui->textEdit->setTextColor( QColor( "red" ) );
        ui->textEdit->insertPlainText(partOfText);

        pos = BitString::convertCoords(i->second) + 1; //update of pos
    }
    partOfText = bitString.mid(pos,-1); //text until end
    ui->textEdit->setTextColor( QColor( "black" ) );
    ui->textEdit->insertPlainText(partOfText);

    delete sim;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
