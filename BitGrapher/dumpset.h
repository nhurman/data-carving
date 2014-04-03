#ifndef DUMPSET_H
#define DUMPSET_H

#include "dump.h"
#include <QString>
#include <QTreeWidgetItem>

class DumpSet
{
public:
    DumpSet();
    DumpSet(QTreeWidgetItem* associatedItem);
    //loads a dump to the dumpSet
    QTreeWidgetItem* addDump(QString fileName);
    //finds a dump in the dumpSet. Returns null if not found
    Dump* find(QString name);
    //removes a dump from the set
    void remove(QString name);

    static std::map<QString, DumpSet*> openedDumpSets;
    static int m_nbNewDumpSets;

private:
    std::map<QString, Dump> m_dumps;
    QTreeWidgetItem* m_associatedItem;

    static QString shortenFileName(QString fileName);
    static QString shortenFileName(std::string fileName);
};

#endif // DUMPSET_H
