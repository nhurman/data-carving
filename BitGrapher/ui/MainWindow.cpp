#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_bitmap(NULL), m_hexView(NULL), m_textView(NULL)
{
    ui->setupUi(this);
    QObject::connect(ui->treeWidget, SIGNAL(selectedDumpChanged(Dump const*)),
        this, SLOT(on_selectedDumpChanged(Dump const*)));

    //on_actionNew_set_triggered();
    //ui->treeWidget->addDump("C:/Users/Nicolas/Desktop/dimp.txt");
    //on_actionText_triggered();

    //resize(BitmapWidget::SquareSize * BitmapWidget::BitsPerLine + 200, 400);
}

MainWindow::~MainWindow()
{
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
        bool ok; //false if cancel was pressed
        QStringList availableImputModes;
        InputFormat guessedFormat = BitString::guessFileInputFormat(filePath.toStdString());
        if(guessedFormat != RAW){
            if(guessedFormat == BINARY){
                availableImputModes.push_back("Binary"); //only available if the guess returns binary (i.e. there were only 0s and 1s in the file)
            }
            availableImputModes.push_back("Hexadecimal"); //only available if not RAW (i.e. if HEXA orBINARY)
        }
        availableImputModes.push_back("Raw data"); //always available

        InputFormat inputFormat;
        if(availableImputModes.size() > 1){ //more than 1 available
            QString chosenFormat = QInputDialog::getItem(this,"Select input format", "Input format : ", availableImputModes, 0, false, &ok);
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

    if (m_bitmap) {
        m_bitmap->setBitString(bs);
    }
    if (m_hexView) {
        m_hexView->setBitString(bs);
    }
    if (m_textView) {
        m_textView->setBitString(bs);
    }
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

void MainWindow::on_actionBitmap_triggered()
{
    delete m_hexView;
    delete m_textView;
    m_hexView = NULL;
    m_textView = NULL;

    if (NULL == m_bitmap) {
        m_bitmap = new BitmapWidget(ui->scrollArea);
        if (NULL != ui->treeWidget->getCurrentDump()) {
            m_bitmap->setBitString(ui->treeWidget->getCurrentDump()->bitString());
        }
    }

    ui->scrollArea->setWidget(m_bitmap);
}

void MainWindow::on_actionHexadecimal_triggered()
{
    delete m_bitmap;
    delete m_textView;
    m_bitmap = NULL;
    m_textView = NULL;

    if (NULL == m_hexView) {
        m_hexView = new HexViewWidget(ui->scrollArea);
        if (NULL != ui->treeWidget->getCurrentDump()) {
            m_hexView->setBitString(ui->treeWidget->getCurrentDump()->bitString());
        }
    }

    if (ui->scrollArea->widget() != m_hexView) {
        ui->scrollArea->setWidget(m_hexView);
    }
}

void MainWindow::on_actionText_triggered()
{
    delete m_bitmap;
    delete m_hexView;
    m_bitmap = 0;
    m_hexView = 0;

    if (!m_textView) {
        m_textView = new TextViewWidget(ui->scrollArea);
        if (ui->treeWidget->getCurrentDump()) {
            m_textView->setBitString(ui->treeWidget->getCurrentDump()->bitString());
        }
    }

    if (ui->scrollArea->widget() != m_textView) {
        ui->scrollArea->setWidget(m_textView);
    }
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
    if(result == NULL)
        return;
    if (result->sameDump()) {
        wid->setBitString(result->getDump1().bitString());
    }
    else {
        wid->setBitStrings(result->getDump1().bitString(),
                           result->getDump2().bitString());
    }
    wid->drawDiagonals();
    wid->show();
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
