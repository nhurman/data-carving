#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DumpSetTreeWidget.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QScrollArea>
#include <QLabel>
#include <QImage>
#include <QDebug>

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
        ui->treeWidget->addDump(filePath);
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
