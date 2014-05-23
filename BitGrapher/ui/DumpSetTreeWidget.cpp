#include "ui/DumpSetTreeWidget.h"


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
    if (ds->fileName().empty()) { //if the dumpSet doesn't exist already (i.e. it is a new dumpSet)
        shortName = "New set (" + QString::number(m_nbNewDumpSets++) + ")"; //Generates a default file name
    }
    else {
        shortName = ds->fileName().c_str(); //Shortens the filepath to get the file name
    }

    QTreeWidgetItem* dumpSetItem = new QTreeWidgetItem(QStringList(shortName)); //Creates the item for the TreeWidget
    //Adds the dumpSet and a blank list of dumps to the model
    m_dumpSets.insert(std::pair<QTreeWidgetItem*, DumpSet*>(dumpSetItem, ds));
    m_dumps.insert(std::make_pair(ds, std::map<QTreeWidgetItem*, Dump const*>()));

    //Adds the dump items to the TreeWidget if any
    for (auto dump: ds->dumps()) {
        QTreeWidgetItem* dumpItem = new QTreeWidgetItem(QStringList(dump.second->fileName().c_str()));
        dumpSetItem->addChild(dumpItem);
        m_dumps[ds].insert(std::make_pair(dumpItem, dump.second));
    }

    //Adds the TreeWidget items to the TreeWidget, and selects them
    addTopLevelItem(dumpSetItem);
    setCurrentItem(dumpSetItem);

    if (dumpSetItem->childCount() > 0) {
        setCurrentItem(dumpSetItem->child(0));
    }
}

void DumpSetTreeWidget::addDump(QString filePath, InputFormat format)
{
    //Checks if a dumpSet was selected
    if (NULL == m_selectedDumpSet) {
        QMessageBox::information(this, "Unable to add dump to set",
            "Please select a dump set.",
            QMessageBox::Ok);
        return;
    }

    //Prevents duplicates
    std::string filePath_c = filePath.toUtf8().constData();
    for (auto i: m_dumps[m_selectedDumpSet]) {
        if (i.second->filePath() == filePath_c) {
            QMessageBox::information(this, "Unable to add dump to set",
                "The dump "  + filePath + " already exists in the current set.",
                QMessageBox::Ok);
            return;
        }
    }

    Dump const* dump = m_selectedDumpSet->add(filePath.toUtf8().constData(), format); //Adds the dump to the dumpSet
    //Creates the item for TreeWidget
    QTreeWidgetItem* dumpSetItem = getDumpSetItem();
    QTreeWidgetItem* dumpItem = new QTreeWidgetItem(QStringList(dump->fileName().c_str()));
    m_dumps[m_selectedDumpSet].insert(std::make_pair(dumpItem, dump)); //Adds the dump to the model
    dumpSetItem->addChild(dumpItem); //Adds the item to treeWidget
    setCurrentItem(dumpItem); //Selects the item
}

void DumpSetTreeWidget::removeDump()
{
    //Checks if a dump was selected
    if (NULL == m_selectedDump) {
        QMessageBox::information(this, "Unable to remove dump",
            "Please select a dump.",
            QMessageBox::Ok);
    }

    //Finds the corresponding item
    QTreeWidgetItem *dumpItem = NULL;
    for (auto i: m_dumps[m_selectedDumpSet]) {
        if (i.second == m_selectedDump) {
            dumpItem = i.first;
            break;
        }
    }

    //Removes the item from TreeWidget
    QTreeWidgetItem* dumpSetItem = getDumpSetItem();
    dumpSetItem->removeChild(dumpItem);
    m_selectedDumpSet->remove(m_selectedDump->filePath()); //Removes the dump from the dumpSet
    m_dumps[m_selectedDumpSet].erase(dumpItem); //Removes the dump from the model
    m_selectedDump = NULL; //Unselects the dump
    emit selectedDumpChanged(m_selectedDump);
}

bool DumpSetTreeWidget::closeDumpSet()
{
    //Checks if a dump was selected
    if (NULL != m_selectedDumpSet) {
        return close(getDumpSetItem());
    }

    return false;
}

bool DumpSetTreeWidget::closeAll()
{
    while (topLevelItemCount() > 0) { //While there are remaining dumpSets
        if (!close(topLevelItem(topLevelItemCount() - 1))) { //Close one
            return false; // If the user aborted the operation, abort
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
    if(i != NULL) //If i exists (i.e the selected item is a Dump)
        return i;
    //else
    return selectedItems().at(0); //the selected item is a DumpSet, return it
}

bool DumpSetTreeWidget::close(QTreeWidgetItem* item)
{
    //Checks if the item exists
    if(item == NULL) {
        return true;
    }

    DumpSet* ds = m_dumpSets[item];
    if(ds->modified()) {
        //Asks the user if he/she wants to save the dumpSet
        QString name = item->text(0);
        int reply = QMessageBox::question(this, name + " is not saved", "Do you want to save " + name + " ?",
            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        switch(reply) {
        case QMessageBox::Yes:
            emit dumpSetNeedsSaving(ds); //Saves it
            break;
        case QMessageBox::Cancel:
            return false; //Aborts
        default: //No
            break; //Proceed as normal
        }
    }

    // Removes dumpset and dumps from model
    m_dumpSets.erase(item);
    m_dumps.erase(ds);

    takeTopLevelItem(indexOfTopLevelItem(item));
    delete ds;

    //Unselects everything
    m_selectedDump = NULL;
    m_selectedDumpSet = NULL;

    //If there are still items left, selects one of them
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
    //Checks if a dumpSet was selected
    if (NULL == m_selectedDumpSet) {
        QMessageBox::information(this, "Unable to save dump set",
            "Please select a dump set.",
            QMessageBox::Ok);
        return;
    }

    //Checks if thd DumpSet already exists, if so it is saved
    if (m_selectedDumpSet->filePath().size() > 0) {
        m_selectedDumpSet->save();
    }
    else { // Else it is saved as... instead
        saveDumpSetAs();
    }
}

void DumpSetTreeWidget::saveDumpSetAs()
{
    //Checks if a dumpSet was selected
    if (NULL == m_selectedDumpSet) {
        QMessageBox::information(this, "Unable to save dump set",
            "Please select a dump set.",
            QMessageBox::Ok);
        return;
    }

    //Asks the user for a file path
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save dump set as..."),
        NULL, tr("Dump Sets (*.ds)"));

    //Saves the DumpSet
    m_selectedDumpSet->save(filePath.toUtf8().constData());

    //Change the item's name in the TreeWidget
    getDumpSetItem()->setText(0, m_selectedDumpSet->fileName().c_str());
}

void DumpSetTreeWidget::openDumpSet()
{
    //Asks the user for a file path
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
        NULL, tr("Dump Sets (*.ds)"));

    //Opens the DumpSet if the user didn't press cancel
    if(filePath.size() > 0) {
        addDumpSet(new DumpSet(filePath.toUtf8().constData()));
    }
}
