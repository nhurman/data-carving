#ifndef DUMPSETTREEWIDGET_H
#define DUMPSETTREEWIDGET_H

#include <QTreeWidget>
#include "dump.h"
#include "dumpset.h"

class DumpSetTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit DumpSetTreeWidget(QWidget *parent = 0);
    void changeDumpSetName(QString name);

signals:
    void selectedDumpChanged(Dump);
    void selectedDumpSetChanged(DumpSet*);

public slots:
    void addDumpSet(DumpSet*);
    void addDump(Dump);
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void closeDumpSet();

private:
    int m_nbNewDumpSets;
    Dump m_selectedDump;
    DumpSet* m_selectedDumpSet;
    std::map<QString, DumpSet*> m_openedDumpSets;

    QTreeWidgetItem* getDumpSetItem();
};

#endif // DUMPSETTREEWIDGET_H
