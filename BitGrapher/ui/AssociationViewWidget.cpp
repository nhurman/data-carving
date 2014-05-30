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
    if (line != -1){
        this->insertRow(line);
    }
    else {
        this->insertRow(0);
    }
}

void AssociationViewWidget::deleteLine()
{
    int line = this->currentRow();
    if (line != -1){
        this->removeRow(line);
    }
    else {
        this->removeRow(this->rowCount()-1);
    }
}

void AssociationViewWidget::openMask() {
    QString line;
    QFile f;
    QStringList rowFields;

    this->closeMask();
    m_filePath = QFileDialog::getOpenFileName(this, tr("Open File"), NULL, tr("Masks (*.mk)"));

    if(m_filePath.size() > 0) { //the user didn't press cancel
        f.setFileName(m_filePath);
        if(f.open(QIODevice::ReadOnly)){
            QTextStream in(&f);
            line = in.readLine();

            while(!line.isNull()) {
                this->insertRow(this->rowCount());
                rowFields = line.split(";");
                for (int column = 0; column < rowFields.size(); column++) {
                    this->setItem(this->rowCount()-1, column, new QTableWidgetItem(rowFields.at(column)));
                }
                line = in.readLine();
            }
        }
    }
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
            for (int j = 0; j < this->columnCount()-1; j++) {
                os << this->item(i,j)->text().toStdString();
                if (j != this->columnCount()-2) {
                     os << ";";

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
    m_filePath = QString();
    return true;
}

void AssociationViewWidget::addLabel(Label l)
{
    insertRow(rowCount());
    setItem(rowCount() - 1, 0, new QTableWidgetItem(l.name.c_str()));
    setItem(rowCount() - 1, 1, new QTableWidgetItem(QString::number(l.index)));
    setItem(rowCount() - 1, 2, new QTableWidgetItem(QString::number(l.length)));
    setItem(rowCount() - 1, 3, new QTableWidgetItem(l.encoding.c_str()));
    setItem(rowCount() - 1, 4, new QTableWidgetItem(l.value.c_str()));
}
