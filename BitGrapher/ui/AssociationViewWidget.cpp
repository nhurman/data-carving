#include "AssociationViewWidget.h"
#include "ui_AssociationViewWidget.h"

AssociationViewWidget::AssociationViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AssociationViewWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Field" << "Value" << "Start" << "Length" << "Encoding");

    connect(ui->Add, SIGNAL(clicked()), this, SLOT(newLine()));
    connect(ui->Delete, SIGNAL(clicked()), this, SLOT(deleteLine()));

    /*ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
    QTableWidgetItem *item = new QTableWidgetItem(QString("coin"));
    ui->tableWidget->setItem(0, 0, item);
    item = new QTableWidgetItem(QString("coin"));
    ui->tableWidget->setItem(0, 1, item);
    item = new QTableWidgetItem(QString("coin"));
    ui->tableWidget->setItem(0, 2, item);
    item = new QTableWidgetItem(QString("coin"));
    ui->tableWidget->setItem(0, 3, item);
    std::cout << ui->tableWidget->rowCount() << " " << ui->tableWidget->columnCount() << std::endl;
    ui->tableWidget->mode*/

}

AssociationViewWidget::~AssociationViewWidget()
{
    delete ui;
}

void AssociationViewWidget::newLine()
{

    int line = ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(line++);
    QTableWidgetItem *item = new QTableWidgetItem (QString());
    ui->tableWidget->setItem(line, 0, item);
    item = new QTableWidgetItem (QString());
    ui->tableWidget->setItem(line, 1, item);
    item = new QTableWidgetItem (QString());
    ui->tableWidget->setItem(line, 2, item);
    item = new QTableWidgetItem (QString());
    ui->tableWidget->setItem(line, 3, item);

}
void AssociationViewWidget::deleteLine()
{
    std::cout << "coin" << std::endl;
}

void AssociationViewWidget::openMask() {
    QString line;
    QFile f;
    QStringList rowFields;

    m_filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
        NULL, tr("Masks (*.mk)"));

    if(m_filePath.size() > 0) { //the user didn't press cancel
        f.setFileName(m_filePath);
        if(f.open(QIODevice::ReadOnly)){
            QTextStream in(&f);
            line = in.readLine();
            while(!line.isNull()) {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                rowFields = line.split(";");
                for (int column = 0; column < rowFields.size(); column++) {
                    ui->tableWidget->item(ui->tableWidget->rowCount(),column)->setText(rowFields[column]);
                }
            }
        }
    }



    /*Association *a = new Association();
    std::vector<struct Field>* fl = a->fieldsLists();

    QTableWidgetItem *item;
    for (int i = 0; i < fl->size(); i++) {
        ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
        item = new QTableWidgetItem(QString(fl->at(i).fieldName.c_str()));
        ui->tableWidget->setItem(i, 0, item);
        //need to decode it ^^
        item = new QTableWidgetItem (QString(a->getBitString()->substring(fl->at(i).start, fl->at(i).end - fl->at(i).start).toString().c_str()));
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem (QString(fl->at(i).start));
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem (QString(fl->at(i).end));
        ui->tableWidget->setItem(i, 3, item);
        //item = new QTableWidgetItem (QString(fl->at(i).decoder.encodingName));
        //model.setItem(i, 4, item);
    }*/
}
bool AssociationViewWidget::saveMaskAs() {
    m_filePath = QFileDialog::getSaveFileName(this, tr("Save this mask as..."),
        NULL, tr("Masks (*.mk)"));
    if(m_filePath.size() == 0) {
        return false;
    }
    return this->saveMask();
}

bool AssociationViewWidget::saveMask() {
    if (m_filePath == NULL) {
        return this->saveMaskAs();
    }
    else {
        std::ofstream os;
        os.open(m_filePath.toStdString(), std::ofstream::out | std::ostream::trunc);
        if (!os.is_open()) {
            return false;
        }
        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
            for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
                os << ui->tableWidget->item(i,j)->text().toStdString() << ";";
            }
            os << std::endl;
        }
        os.close();
        return true;
    }
}
