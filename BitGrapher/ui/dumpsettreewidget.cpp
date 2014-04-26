#include "ui/dumpsettreewidget.h"
#include <QMessageBox>
#include <QFileDialog>

DumpSetTreeWidget::DumpSetTreeWidget(QWidget *parent) :
    QTreeWidget(parent), m_nbNewDumpSets(0), m_selectedDumpSet(NULL), m_selectedDump(NULL)
{
    QObject::connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
        this, SLOT(onCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
}

Dump const* DumpSetTreeWidget::getCurrentDump()
{
    return m_selectedDump;
}

DumpSet* DumpSetTreeWidget::getCurrentDumpSet()
{
    return m_selectedDumpSet;
}

void DumpSetTreeWidget::addDumpSet(DumpSet* ds)
{
    QString shortName;
    if (ds->fileName().empty()) {
        shortName = "New set (" + QString::number(m_nbNewDumpSets++) + ")";
    }
    else {
        shortName = ds->fileName().c_str();
    }

    QTreeWidgetItem* dumpSetItem = new QTreeWidgetItem(QStringList(shortName));
    m_dumpSets.insert(std::pair<QTreeWidgetItem*, DumpSet*>(dumpSetItem, ds));
    m_dumps.insert(std::make_pair(ds, std::map<QTreeWidgetItem*, Dump const*>()));

    for (auto dump: ds->dumps()) {
        QTreeWidgetItem* dumpItem = new QTreeWidgetItem(QStringList(dump.second->fileName().c_str()));
        dumpSetItem->addChild(dumpItem);
        m_dumps[ds].insert(std::make_pair(dumpItem, dump.second));
    }

    addTopLevelItem(dumpSetItem);
    setCurrentItem(dumpSetItem);

    if (dumpSetItem->childCount() > 0) {
        setCurrentItem(dumpSetItem->child(0));
    }
}

void DumpSetTreeWidget::addDump(QString filePath, InputFormat format)
{
    if (NULL == m_selectedDumpSet) {
        return;
    }

    std::string filePath_c = filePath.toUtf8().constData();
    for (auto i: m_dumps[m_selectedDumpSet]) {
        if (i.second->filePath() == filePath_c) {
            return;
        }
    }

    Dump const* dump = m_selectedDumpSet->add(filePath.toUtf8().constData(), format);
    QTreeWidgetItem* dumpSetItem = getDumpSetItem();
    QTreeWidgetItem* dumpItem = new QTreeWidgetItem(QStringList(dump->fileName().c_str()));
    m_dumps[m_selectedDumpSet].insert(std::make_pair(dumpItem, dump));
    dumpSetItem->addChild(dumpItem);
    setCurrentItem(dumpItem);
}

void DumpSetTreeWidget::removeDump()
{
    if (NULL == m_selectedDump) {
        return;
    }

    QTreeWidgetItem *dumpItem = NULL;
    for (auto i: m_dumps[m_selectedDumpSet]) {
        if (i.second == m_selectedDump) {
            dumpItem = i.first;
            break;
        }
    }

    QTreeWidgetItem* dumpSetItem = getDumpSetItem();
    dumpSetItem->removeChild(dumpItem);
    m_selectedDumpSet->remove(m_selectedDump->filePath());
    m_dumps[m_selectedDumpSet].erase(dumpItem);
    m_selectedDump = NULL;
    emit selectedDumpChanged(m_selectedDump);
}

bool DumpSetTreeWidget::closeDumpSet()
{
    if (NULL != m_selectedDumpSet) {
        return close(getDumpSetItem());
    }

    return false;
}

bool DumpSetTreeWidget::closeAll()
{
    while (topLevelItemCount() > 0) {
        if (!close(topLevelItem(topLevelItemCount() - 1))) { //if the user aborted the operation
            return false;
        }
    }

    return true;
}

void DumpSetTreeWidget::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (current != NULL)  {
        if (current->parent() == NULL) { //if a dumpset was selected
            m_selectedDumpSet = m_dumpSets[current];
            emit selectedDumpSetChanged(m_selectedDumpSet);
        }
        else { //if a dump was selected
            if (!previous || current->parent() != previous->parent() || current->parent() != previous) { //if the dumpset has changed
                m_selectedDumpSet = m_dumpSets[current->parent()];
                emit selectedDumpSetChanged(m_selectedDumpSet);
            }

            m_selectedDump = m_dumps[m_selectedDumpSet][current];
            emit selectedDumpChanged(m_selectedDump);
        }
    }
}

QTreeWidgetItem* DumpSetTreeWidget::getDumpSetItem()
{
    QTreeWidgetItem* i = selectedItems().at(0)->parent();
    if(i != NULL)
        return i;
    return selectedItems().at(0);
}

bool DumpSetTreeWidget::close(QTreeWidgetItem* item)
{
    if(item == NULL) {
        return true;
    }

    DumpSet* ds = m_dumpSets[item];
    if(ds->modified()) {
        QString name = item->text(0);
        int reply = QMessageBox::question(this, name + " is not saved", "Do you want to save " + name + " ?",
            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        switch(reply) {
        case QMessageBox::Yes:
            emit dumpSetNeedsSaving(ds);
            break;
        case QMessageBox::Cancel:
            return false;
        default: //No
            break;
        }
    }

    // Remove dumpset and dumps from model
    m_dumpSets.erase(item);
    m_dumps.erase(ds);

    takeTopLevelItem(indexOfTopLevelItem(item));
    delete ds;

    m_selectedDump = NULL;
    m_selectedDumpSet = NULL;

    if (topLevelItemCount() > 0) {
        m_selectedDumpSet = m_dumpSets[topLevelItem(0)];
        setCurrentItem(topLevelItem(0));
        if (topLevelItem(0)->childCount() > 0) {
            m_selectedDump = m_dumps[m_selectedDumpSet][topLevelItem(0)->child(0)];
            setCurrentItem(topLevelItem(0)->child(0));
        }
    }

    emit selectedDumpChanged(m_selectedDump);
    emit selectedDumpSetChanged(m_selectedDumpSet);
    return true;
}


void DumpSetTreeWidget::saveDumpSet()
{
    if (NULL == m_selectedDumpSet) {
        QMessageBox::information(this, "Unable to save dump set",
            "Please select a dump set.",
            QMessageBox::Ok);
        return;
    }

    if (m_selectedDumpSet->filePath().size() > 0) {
        m_selectedDumpSet->save();
    }
    else { // Save as instead
        saveDumpSetAs();
    }
}

void DumpSetTreeWidget::saveDumpSetAs()
{
    if (NULL == m_selectedDumpSet) {
        QMessageBox::information(this, "Unable to save dump set",
            "Please select a dump set.",
            QMessageBox::Ok);
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, tr("Save dump set as..."),
        NULL, tr("Dump Sets (*.ds)"));

    m_selectedDumpSet->save(filePath.toUtf8().constData());
}

void DumpSetTreeWidget::openDumpSet()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
        NULL, tr("Dump Sets (*.ds)"));

    if(filePath.size() > 0) { //the user didn't press cancel
        addDumpSet(new DumpSet(filePath.toUtf8().constData()));
    }
}
