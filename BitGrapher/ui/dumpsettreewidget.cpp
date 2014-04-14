#include "ui/dumpsettreewidget.h"
#include <QMessageBox>

DumpSetTreeWidget::DumpSetTreeWidget(QWidget *parent) :
    QTreeWidget(parent), m_nbNewDumpSets(0)
{
    QObject::connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
                          this, SLOT(onCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
}

Dump DumpSetTreeWidget::getCurrentDump()
{
    return m_selectedDump;
}

DumpSet* DumpSetTreeWidget::getCurrentDumpSet()
{
    return m_selectedDumpSet;
}

void DumpSetTreeWidget::addDump(Dump d)
{

    m_selectedDumpSet->addDump(d);
    QTreeWidgetItem* dSItem = getDumpSetItem();
    QTreeWidgetItem* child = new QTreeWidgetItem(QStringList(d.getShortName()));
    dSItem->addChild(child);
    setCurrentItem(child);
}

void DumpSetTreeWidget::addDumpSet(DumpSet* ds)
{
    QString shortName = ds->getShortName();
    if(shortName == "")
        shortName = "NewDumpSet_" + QString::number(m_nbNewDumpSets++);
    m_openedDumpSets[shortName] = ds;
    //m_selectedDumpSet = ds;
    QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(shortName));
    std::vector<QString> dumps = ds->getDumpNames();
    unsigned int i;
    for(i = 0; i < dumps.size(); i++)
    {
        item->addChild(new QTreeWidgetItem(QStringList(dumps.at(i))));
    }
    addTopLevelItem(item);
    setCurrentItem(item);
    if(i > 0)
    {
        setCurrentItem(item->child(0));
    }
}

void DumpSetTreeWidget::changeDumpSetName(QString name)
{
    if(m_selectedDumpSet != NULL)
    {
        m_openedDumpSets.erase(m_selectedDumpSet->getShortName());
        m_selectedDumpSet->setFileName(name);
        QString shortName = m_selectedDumpSet->getShortName();
        m_openedDumpSets[shortName] = m_selectedDumpSet;
        getDumpSetItem()->setText(0,shortName);
    }
}

bool DumpSetTreeWidget::closeDumpSet()
{
    bool b = close(getDumpSetItem());
    m_selectedDumpSet = NULL;
    return b;
}

bool DumpSetTreeWidget::closeAll()
{
    while (topLevelItemCount() > 0)
    {
        if(!close(topLevelItem(topLevelItemCount()-1))) //if the user aborted the closure
            return false;
    }
    m_selectedDumpSet = NULL;
    return true;
}

void DumpSetTreeWidget::selectDump(QString dumpName)
{
    QTreeWidgetItem* item;
    for(int i = 0; i < getDumpSetItem()->childCount(); i++)
    {
        if((item = getDumpSetItem()->child(i))->text(0) == dumpName)
        {
            setCurrentItem(item);
            return;
        }
    }
}

void DumpSetTreeWidget::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current != NULL)
    {
        if(current->parent() == NULL) //if a dumpset was selected
        {
            m_selectedDumpSet = m_openedDumpSets[current->text(0)];
            //std::cout<<"toplevel"<<std::endl;
            emit selectedDumpSetChanged(m_selectedDumpSet);
        }
        else //if a dump is selected
        {
            if(current->parent() != previous->parent() || current->parent() != previous) //if the dumpset has changed
            {
                m_selectedDumpSet = m_openedDumpSets[current->parent()->text(0)];
                //std::cout<<"new parent"<<std::endl;
                emit selectedDumpSetChanged(m_selectedDumpSet);
            }
            m_selectedDump = *m_selectedDumpSet->find(current->text(0));
            //std::cout<<"lowlevel"<<std::endl;
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
    if(item == NULL)
        return true;

    QString name = item->text(0);
    DumpSet* ds = m_openedDumpSets[name];
    if(ds == NULL)
        return true;

    if(ds->isModified())
    {
        int reply = QMessageBox::question(this, name+" is not saved", "Do you want to save "+name+" ?",
                                        QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        switch(reply)
        {
        case QMessageBox::Yes:
            emit dumpSetNeedsSaving(ds);
            break;
        case QMessageBox::Cancel:
            return false;
        default: //No
            break;
        }
    }

    m_openedDumpSets.erase(name);
    delete item; //apparently a safe way to remove the item
    delete ds;
    return true;
}