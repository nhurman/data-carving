#ifndef DUMPSET_H
#define DUMPSET_H

#include "dump.h"
#include <QString>
#include <QTreeWidgetItem>

class DumpSet
{
public:
    DumpSet(QString fileName = "");
    void setFileName(QString fileName);
    QString getShortName();
    bool hasName();
    bool isModified();
    //loads a dump to the dumpSet
    void addDump(Dump d);
    void addDump(QString fileName);
    //finds a dump in the dumpSet. Returns null if not found
    Dump* find(QString name);
    //removes a dump from the set
    void remove(QString name);
    std::vector<QString> getDumpNames();
    bool saveToFile(QString fileName);
    bool save();

private:
    std::map<QString, Dump> m_dumps;
    QString m_fileName;
    bool m_modified;

    static QString shortenFileName(QString filePath);
    static QString shortenFileName(std::string fileName);
};

#endif // DUMPSET_H
