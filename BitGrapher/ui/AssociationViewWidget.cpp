#include "AssociationViewWidget.h"
#include <QDebug>

#include "encoding/BCD.h"
#include "encoding/ASCII7.h"
#include "encoding/ASCII8.h"
#include "encoding/Binary.h"
#include "encoding/Integer.h"

AssociationViewWidget::AssociationViewWidget(QWidget *parent) :
    QTableWidget(parent)
{
    m_encodings["ASCII (7 bits)"] = new ASCII7();
    m_encodings["ASCII (8 bits)"] = new ASCII8();
    m_encodings["BCD"] = new BCD();
    m_encodings["Binary"] = new Binary();
    m_encodings["Int2"] = new Integer2();
    m_encodings["Int3"] = new Integer3();
    m_encodings["Int4"] = new Integer4();
    m_encodings["Int5"] = new Integer5();
    m_encodings["Int6"] = new Integer6();
    m_encodings["Int7"] = new Integer7();
    m_encodings["Int8"] = new Integer8();
    m_encodings["Int16"] = new Integer16();
    m_encodings["Int32"] = new Integer32();
    m_bitString = 0;
}

void AssociationViewWidget::setBitString(BitString const* bs)
{
    m_bitString = bs;
    for (auto e: m_encodings) {
        e->setBitString(bs);
    }

    for (int i = 0; i < rowCount(); ++i) {
        updateLabel(i, getLabel(i));
    }
}

QMap<QString, Encoding2*>* AssociationViewWidget::getEncodings()
{
    return &m_encodings;
}

AssociationViewWidget::~AssociationViewWidget()
{
    qDeleteAll(m_encodings);
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
                rowFields = line.split(";");
                Label l;
                l.name = rowFields.at(0).toUtf8().constData();
                l.index = rowFields.at(1).toInt();
                l.length = rowFields.at(2).toInt();
                l.encoding = rowFields.at(3).toUtf8().constData();
                addLabel(l);
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
    updateLabel(rowCount() - 1, l);
}

Label AssociationViewWidget::getLabel(int row)
{
    Label l;
    l.name = item(row, 0)->text().toUtf8().constData();
    l.index = item(row, 1)->text().toInt();
    l.length = item(row, 2)->text().toInt();
    l.encoding = item(row, 3)->text().toUtf8().constData();
    l.value = item(row, 4)->text().toUtf8().constData();
    return l;
}

void AssociationViewWidget::updateLabel(int row, Label l)
{
    setItem(row, 0, new QTableWidgetItem(l.name.c_str()));
    setItem(row, 1, new QTableWidgetItem(QString::number(l.index)));
    setItem(row, 3, new QTableWidgetItem(l.encoding.c_str()));

    Encoding2* e = m_encodings[l.encoding.c_str()];
    if (l.length % e->bitsPerChunk() > 0) {
        l.length += e->bitsPerChunk() - (l.length % e->bitsPerChunk());
    }

    setItem(row, 2, new QTableWidgetItem(QString::number(l.length)));
    QString value = e->decode(l.index, l.length).c_str();
    setItem(row, 4, new QTableWidgetItem(value));
}

