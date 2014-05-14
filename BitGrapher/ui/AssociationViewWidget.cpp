#include "AssociationViewWidget.h"

AssociationViewWidget::AssociationViewWidget(QWidget *parent) :
    QTableWidget(parent)
{
}

AssociationViewWidget::~AssociationViewWidget()
{
}

void AssociationViewWidget::newLine()
{

    int line = this->currentRow();
    this->insertRow(line++);
    QTableWidgetItem *item = new QTableWidgetItem (QString());
    this->setItem(line, 0, item);
    item = new QTableWidgetItem (QString());
    this->setItem(line, 1, item);
    item = new QTableWidgetItem (QString());
    this->setItem(line, 2, item);
    item = new QTableWidgetItem (QString());
    this->setItem(line, 3, item);

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
                this->insertRow(this->rowCount());
                rowFields = line.split(";");
                for (int column = 0; column < rowFields.size(); column++) {
                    this->item(this->rowCount(),column)->setText(rowFields[column]);
                }
            }
        }
    }

    /*Association *a = new Association();
    std::vector<struct Field>* fl = a->fieldsLists();

    QTableWidgetItem *item;
    for (int i = 0; i < fl->size(); i++) {
        this->insertRow( this->rowCount() );
        item = new QTableWidgetItem(QString(fl->at(i).fieldName.c_str()));
        this->setItem(i, 0, item);
        //need to decode it ^^
        item = new QTableWidgetItem (QString(a->getBitString()->substring(fl->at(i).start, fl->at(i).end - fl->at(i).start).toString().c_str()));
        this->setItem(i, 1, item);
        item = new QTableWidgetItem (QString(fl->at(i).start));
        this->setItem(i, 2, item);
        item = new QTableWidgetItem (QString(fl->at(i).end));
        this->setItem(i, 3, item);
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
        for (int i = 0; i < this->rowCount(); i++) {
            for (int j = 0; j < this->columnCount(); j++) {
                if (j != 1) { //to avoid writing data field
                    os << this->item(i,j)->text().toStdString() << ";";
                }
            }
            os << std::endl;
        }
        os.close();
        return true;
    }
}

bool AssociationViewWidget::closeMask(){
    while(this->rowCount() > 0) {
        this->removeRow(0);
    }
    return true;
}
