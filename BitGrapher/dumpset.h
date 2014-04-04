#ifndef DUMPSET_H
#define DUMPSET_H

#include "dump.h"
#include <QString>
#include <QTreeWidgetItem>

class DumpSet
{
public:
    DumpSet(QString fileName = "");
    DumpSet(QTreeWidgetItem* associatedItem, QString fileName ="");
    void setFileName(QString fileName);
    bool hasName();
    //loads a dump to the dumpSet
    QTreeWidgetItem* addDump(QString fileName);
    //finds a dump in the dumpSet. Returns null if not found
    Dump* find(QString name);
    //removes a dump from the set
    void remove(QString name);
    bool saveToFile(QString fileName);
    bool save();

    static QTreeWidgetItem* openFromFile(QString fileName);
    static std::map<QString, DumpSet*> m_openedDumpSets;
    static int m_nbNewDumpSets;

private:
    std::map<QString, Dump> m_dumps;
    QTreeWidgetItem* m_associatedItem;
    QString m_fileName;

    void changeFileName(QString name);

    static QString shortenFileName(QString filePath);
    static QString shortenFileName(std::string fileName);
};

#endif // DUMPSET_H
