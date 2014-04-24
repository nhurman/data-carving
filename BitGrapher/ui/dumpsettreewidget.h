#ifndef DUMPSETTREEWIDGET_H
#define DUMPSETTREEWIDGET_H

#include <QTreeWidget>
#include "core/Dump.h"
#include "core/DumpSet.h"

class DumpSetTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit DumpSetTreeWidget(QWidget *parent = 0);
    void changeDumpSetName(QString name);
    Dump const* getCurrentDump();
    DumpSet* getCurrentDumpSet();
    void saveDumpSet();
    void saveDumpSetAs();
    void openDumpSet();

signals:
    void selectedDumpChanged(Dump const*);
    void selectedDumpSetChanged(DumpSet*);
    void dumpSetNeedsSaving(DumpSet*);

public slots:
    void addDumpSet(DumpSet*);
    void addDump(QString filePath);
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    //returns false if the closure was aborted by the user
    bool closeDumpSet();
    void removeDump();
    //returns false if the closure was aborted by the user
    bool closeAll();

private:
    typedef std::map<DumpSet*, std::map<QTreeWidgetItem*, Dump const*>> DumpSetMap;

    int m_nbNewDumpSets;
    DumpSet* m_selectedDumpSet;
    Dump const* m_selectedDump;
    std::map<QTreeWidgetItem*, DumpSet*> m_dumpSets;
    DumpSetMap m_dumps;

    QTreeWidgetItem* getDumpSetItem();
    bool close(QTreeWidgetItem* item);
};

#endif // DUMPSETTREEWIDGET_H
