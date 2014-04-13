#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bitstring.h"
#include "similaritesdialog.h"
#include "encodingsdialog.h"
#include <iostream>

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_charSize(1)
{
    ui->setupUi(this);

    //ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    m_dumpSet = NULL;
    m_bitstring = new BitString("615B5F1F");//58503C42454C56414E4445523C4D45554C454E3C3C4A4F53453C483C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C45463437383539373C3942454C383030313136324D313130333231383C3C3C3C3C3C3C3C3C3C3C3C3C3C3034");
    BitString bs("F15B5F1F58503C42454C56414E4445523C4D45554C454E3C3C4A4F53453C483C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C3C45463437383539373C3942454C383030313136324D313130333231383C3C3C3C3C3C3C3C3C3C3C3C3C3C3034");
    m_bitstring->bitOr(bs);
    ui->textEdit->setText(m_bitstring->toString().c_str());
    ui->graphArea->setBitString(m_bitstring);

QObject::connect(ui->treeWidget, SIGNAL (dumpSetNeedsSaving(DumpSet*)),
                 this, SLOT (saveDumpSet(DumpSet*)));

    /* ---------------- TESTS -------------- */
    /*              To be moved              */

    Similarities::test();

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
    std::list<Diagonal> listdiag = testDiag1.dotPlotPattern(&testDiag2);
    std::cout << "Dotplot Pattern : " << listdiag.size() << std::endl;
    for (std::list<Diagonal>::iterator i = listdiag.begin(); i != listdiag.end(); i++ ){
        std::cout << "Diag " << (*i).toString() << std::endl ;
    }


    /* ------------------------------------- */

    std::cout << std::endl;
    BitString testEncode1("48414c50");
    std::cout << testEncode1.toString() << " " <<  (unsigned int)(testEncode1.getByte(17))<<  " " << (unsigned int) Encoding::switchEndian(testEncode1.getByte(17)) << std::endl;
    std::cout << Encoding::encode(testEncode1, Encoding::switchEndian, 0, 0, 8) << std::endl;
    std::cout << Encoding::encode(testEncode1, Encoding::reverseHexadecimal, 0, 0, 4) << std::endl;

    std::cout << std::endl;
    BitString testEncode2("F48414c50F");
    std::cout << testEncode2.toString() <<  std::endl;
    std::cout << Encoding::encode(testEncode2, Encoding::switchEndian, 4, 0, 8) << std::endl;
    std::cout << Encoding::encode(testEncode2, Encoding::reverseHexadecimal, 0, 0, 4) << std::endl;

    std::cout << std::endl;
    BitString testEncode3("2420a62800");
    std::cout << testEncode3.toString() <<  std::endl;
    std::cout << Encoding::encode(testEncode3, Encoding::switchEndian, 1, 0, 8) << std::endl;
    std::cout << Encoding::encode(testEncode3, Encoding::reverseHexadecimal, 0, 0, 4) << std::endl;

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
    if(fileName != "") //the user didn't press cancel
        ui->treeWidget->addDumpSet(new DumpSet(fileName));

}

void MainWindow::saveDumpSet(DumpSet* ds)
{
    if(ds != NULL)
    {
        if(ds->hasName())
            ds->save();
        else
            saveDumpSetAs(ds); //save as instead
    }
    else //no dump set selected
    {
        QMessageBox::information(this, "Unable to save dump set",
                                 "Please select a dump set.",
                                 QMessageBox::Ok);
    }
}

void MainWindow::saveDumpSetAs(DumpSet* ds)
{
    if(ds != NULL)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save dump set as..."),
                                                         DEFAULT_DIRECTORY,
                                                         tr("Dump Sets (*.ds)"));
        if(ds->saveToFile(fileName))
        {
            ui->treeWidget->changeDumpSetName(fileName);
        }
    }
    else //no dump set selected
    {
        QMessageBox::information(this, "Unable to save dump set",
                                 "Please select a dump set.",
                                 QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_triggered()
{
    saveDumpSet(m_dumpSet);
}

void MainWindow::on_actionSave_as_triggered()
{
    saveDumpSetAs(m_dumpSet);
}

void MainWindow::on_actionDiagonals_View_triggered(){
    std::cout << "Diagonals !" << std::endl ;

    if(m_dumpSet == NULL) //no dump selected
    {
        QMessageBox::information(this, "Could not perform operation",
                                 "Please select a dump in a dump set.",
                                 QMessageBox::Ok);
        return;
    }
    else if (m_dumpSet->size() == 1) {
        std::map<QString, Dump>::iterator it =  m_dumpSet->getDumps().begin();
        m_dpgraph.setBitString(it->second.getBitString());
        m_dpgraph.setDiagonals(it->second.getBitString()->dotPlotPattern());

    }
    else if (m_dumpSet->size() == 2) {
        std::map<QString, Dump>::iterator it =  m_dumpSet->getDumps().begin();
        BitString *b1 = it->second.getBitString();
        BitString *b2 = (++it)->second.getBitString();
        m_dpgraph.setBitStrings(b1, b2);
        m_dpgraph.setDiagonals((*b1).dotPlotPattern(b2));
    }
    else {
        QMessageBox::information(this, "Could not perform operation",
                                 "Please select one or two dump in a dump set.",
                                 QMessageBox::Ok);
        return;
    }
    m_dpgraph.show();
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

        std::map<DumpSet*, Similarities*>::iterator i = m_similarities.find(m_dumpSet);
        if( i != m_similarities.end())
        {
            int id = i->second->getDumpId(ui->treeWidget->getCurrentDump());
            if(id != -1)
                drawSimilarities(i->second, id);
        }
    }
    else
    {
        QMessageBox::warning(this, "Could not find dump",
                                 "There is no selected dump",
                                 QMessageBox::Ok);
    }
}

void MainWindow::drawSimilarities(Similarities* s, int dumpId)
{
    QString bitString = QString::fromStdString(m_bitstring->toString());
    ui->textEdit->clear();
    QString partOfText;
    int pos = 0;
    std::list< SIM_TYPE >* list = s->getList();
    for (std::list< SIM_TYPE >::iterator i = list->begin(); i != list->end(); i++ )
    {
        int length = convertCoords(i->first.first, true)-pos;
        partOfText = bitString.mid(pos,length); //text until next highlight
        ui->textEdit->setTextColor( QColor( DISSIM_COLOR ) );
        ui->textEdit->insertPlainText(partOfText);

        pos = convertCoords(i->first.first, true);
        length = convertCoords(i->first.second) - pos + 1;
        partOfText = bitString.mid(pos, length); //highlighted text
        float ratio = (float) i->second.size()/s->getDumpCount();
        if(std::find(i->second.begin(), i->second.end(), dumpId) != i->second.end()) //the similarity concerne the selected dump
            ui->textEdit->setTextColor( makeColor(QColor( SIM_COLOR ), QColor( DISSIM_COLOR ), ratio) );
        else
            ui->textEdit->setTextColor( makeColor(QColor( OTHER_SIM_COLOR ), QColor( DISSIM_COLOR ), ratio) );
        ui->textEdit->insertPlainText(partOfText);

        pos = convertCoords(i->first.second) + 1; //update of pos
    }
    partOfText = bitString.mid(pos,-1); //text until end
    ui->textEdit->setTextColor( QColor( DISSIM_COLOR ) );
    ui->textEdit->insertPlainText(partOfText);
    ui->textEdit->setTextColor( QColor( DEFAULT_COLOR ) );
}

void MainWindow::on_actionAdd_Dump_to_Set_triggered()
{
    if(m_dumpSet == NULL) //no dump set yet
    {
        QMessageBox::information(this, "Could not insert dump",
                                 "Please select a dump set to insert the dump into.",
                                 QMessageBox::Ok);
        return;
    }
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

    if(m_dumpSet->getDumpNames().size() < 2) //not enough dumps for comparison
    {
        QMessageBox::information(this, "Could not perform operation",
                                 "Not enough dumps in the dump set (at least 2 necessary)",
                                 QMessageBox::Ok);
        return;
    }

    QString* dumpName = new QString;

    Similarities* sim = SimilaritesDialog::getSimilarities(m_dumpSet, dumpName);
    if(sim == NULL) //cancel was pressed
        return;
    else
    {
        if(m_similarities.find(m_dumpSet) != m_similarities.end()) //there is already a similarities in the dump set
        {
            delete m_similarities[m_dumpSet]; //delete it
            m_similarities.erase(m_dumpSet);
        }
        m_similarities[m_dumpSet] = sim; //add the new similarities
    }

    ui->treeWidget->selectDump(*dumpName);

    refreshDisplay(); //refreshes to show similarities. Only useful if the selected dump has not changed
}

void MainWindow::on_actionEncodings_triggered()
{
    EncodingsDialog encodingDialog(this, ui->textEdit, m_bitstring);
    encodingDialog.exec();
}

void MainWindow::on_actionExit_triggered()
{
    if(on_actionClose_all_triggered()) //closes all dump sets before exiting and checks the operation was not aborted
        close();
}

bool MainWindow::on_actionClose_all_triggered()
{
    return ui->treeWidget->closeAll();
}

QColor MainWindow::makeColor(QColor c1, QColor c2, float ratio)
{
    return QColor (c1.red()*ratio + c2.red()*(1-ratio),
                   c1.green()*ratio + c2.green()*(1-ratio),
                   c1.blue()*ratio + c2.blue()*(1-ratio));
}

int MainWindow::convertCoords(int c, bool roundUp)
{
    if(m_charSize == 1)
        return BitString::convertCoords(c);
    //else
    int res = c/m_charSize;
    if(roundUp && c%m_charSize==0)
        res ++;
    return res;
}
