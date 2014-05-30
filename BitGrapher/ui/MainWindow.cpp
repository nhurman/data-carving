#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->treeWidget, SIGNAL(selectedDumpChanged(Dump const*)),
        this, SLOT(on_selectedDumpChanged(Dump const*)));

    on_actionNew_set_triggered();
    //ui->treeWidget->addDump("C:/Users/Nicolas/Desktop/dimp.txt");

    m_txtView = ui->txtView;
    m_hexView = new HexViewWidget(ui->hexScroll);
    m_bmpView = new BitmapWidget(ui->bmpScroll);

    ui->hexScroll->setWidget(m_hexView);
    ui->bmpScroll->setWidget(m_bmpView);
}

MainWindow::~MainWindow()
{
    delete m_bmpView;
    delete m_hexView;
    delete ui;
}

void MainWindow::on_actionAdd_dump_triggered()
{
    if (ui->treeWidget->getCurrentDumpSet() == NULL) {
        QMessageBox::information(this, "Could not insert dump",
            "Please select a dump set to insert the dump into.",
            QMessageBox::Ok);
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(this, tr("Open dump file"),
        NULL, tr("Files (*.*)"));

    if(filePath.size() > 0) {
        //asking for file format
        bool ok = true; //false if cancel was pressed
        QStringList availableInputModes;
        InputFormat guessedFormat = BitString::guessFileInputFormat(filePath.toStdString());
        if(guessedFormat != RAW){
            if(guessedFormat == BINARY){
                availableInputModes.push_back("Binary"); //only available if the guess returns binary (i.e. there were only 0s and 1s in the file)
            }
            availableInputModes.push_back("Hexadecimal"); //only available if not RAW (i.e. if HEXA orBINARY)
        }
        availableInputModes.push_back("Raw data"); //always available

        InputFormat inputFormat;
        if(availableInputModes.size() > 1){ //more than 1 available
            QString chosenFormat = QInputDialog::getItem(this,"Select input format", "Input format : ", availableInputModes, 0, false, &ok);
            if(ok){ //cancel was not pressed
                inputFormat = BitString::stringToFormat(chosenFormat.toStdString());
            }
            //else we won't add the dump, so nothing more to do
        }
        else{
            inputFormat = RAW; //default value
        }
        if(ok)
            ui->treeWidget->addDump(filePath, inputFormat);
    }
}

void MainWindow::on_selectedDumpChanged(Dump const* dump)
{
    BitString const* bs = NULL;
    if (dump) {
        bs = dump->bitString();
    }

    m_txtView->setBitString(bs);
    m_hexView->setBitString(bs);
    m_bmpView->setBitString(bs);
}

void MainWindow::on_actionNew_set_triggered()
{
    ui->treeWidget->addDumpSet(new DumpSet());
}

void MainWindow::on_actionRemove_dump_triggered()
{
    ui->treeWidget->removeDump();
}

void MainWindow::on_actionClose_set_triggered()
{
    ui->treeWidget->closeDumpSet();
}

void MainWindow::on_actionOpen_set_triggered()
{
    ui->treeWidget->openDumpSet();
}

void MainWindow::on_actionSave_set_triggered()
{
    ui->treeWidget->saveDumpSet();
}

void MainWindow::on_actionSave_set_as_triggered()
{
    ui->treeWidget->saveDumpSetAs();
}

void MainWindow::on_action_Dot_Plot_Pattern_triggered()
{
    if(ui->treeWidget->getCurrentDumpSet() == NULL) //no dump selected
    {
        QMessageBox::information(this, "Could not perform operation",
                                 "Please select a dump in a dump set.",
                                 QMessageBox::Ok);
        return;
    }

    if(ui->treeWidget->getCurrentDumpSet()->getDumpNames().size() < 1) //not enough dumps for comparison
    {
        QMessageBox::information(this, "Could not perform operation",
                                 "Not enough dumps in the dump set (at least 1 necessary)",
                                 QMessageBox::Ok);
        return;
    }

    DotPlotView *wid = new DotPlotView();
    DotPlotDialog *dialog = new DotPlotDialog(this, ui->treeWidget->getCurrentDumpSet());

    dialog->exec();
    DotPlotResult* result = dialog->getResult();
    if(result == NULL) {
        delete wid;
        return;
    }
    else if (result->sameDump()) {
        wid->setBitString(result->getDump1().bitString(), result->getDiagSize());
        wid->setWindowTitle(QString(result->getDump1().fileName().c_str()));
        wid->show();
    }
    else {
        wid->setBitStrings(result->getDump1().bitString(), result->getDump2().bitString(), result->getDiagSize());
        wid->setWindowTitle(QString(result->getDump1().fileName().c_str()), QString(result->getDump2().fileName().c_str()));
        wid->show();
    }
    /*DotPlotView *wid = new DotPlotView();
    wid->show();*/
}

void MainWindow::on_actionOpen_Mask_triggered()
{
    ui->tableWidget->openMask();
}

void MainWindow::on_actionClose_Mask_triggered()
{
    ui->tableWidget->closeMask();
}

void MainWindow::on_actionSave_Mask_triggered()
{
    ui->tableWidget->saveMask();
}

void MainWindow::on_actionSave_As_triggered()
{
    ui->tableWidget->saveMaskAs();
}

void MainWindow::on_actionNew_Line_triggered()
{
    ui->tableWidget->newLine();
}

void MainWindow::on_actionDelete_Line_triggered()
{
    ui->tableWidget->deleteLine();
}

void MainWindow::on_actionSimilarities_triggered()
{
    DumpSet* ds = ui->treeWidget->getCurrentDumpSet();
    if(ds == NULL) //no dump selected
    {
        QMessageBox::information(this, "Could not perform operation",
                                 "Please select a dump in a dump set.",
                                 QMessageBox::Ok);
        return;
    }

    if(ds->size() < 2) //not enough dumps for comparison
    {
        QMessageBox::information(this, "Could not perform operation",
                                 "Not enough dumps in the dump set (at least 2 necessary)",
                                 QMessageBox::Ok);
        return;
    }

    Dump const* dump;

    Similarities* sim = SimilaritiesDialog::getSimilarities(ds, dump);
    //if(sim == NULL) //cancel was pressed
    //    return;
    //else
    //{
    //    if(m_similarities.find(m_dumpSet) != m_similarities.end()) //there is already a similarities in the dump set
    //    {
    //        delete m_similarities[m_dumpSet]; //delete it
    //        m_similarities.erase(m_dumpSet);
    //    }
    //    m_similarities[m_dumpSet] = sim; //add the new similarities
    //}

    //ui->treeWidget->selectDump(*dumpName);

    //refreshDisplay(); //refreshes to show similarities. Only useful if the selected dump has not changed
}
