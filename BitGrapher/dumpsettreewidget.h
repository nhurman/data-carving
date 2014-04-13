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
    Dump getCurrentDump();
    DumpSet* getCurrentDumpSet();

signals:
    void selectedDumpChanged(Dump);
    void selectedDumpSetChanged(DumpSet*);
    void dumpSetNeedsSaving(DumpSet*);

public slots:
    void addDumpSet(DumpSet*);
    void addDump(Dump);
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    //returns false if the closure was aborted by the user
    bool closeDumpSet();
    //returns false if the closure was aborted by the user
    bool closeAll();
    void selectDump(QString dumpName);

private:
    int m_nbNewDumpSets;
    Dump m_selectedDump;
    DumpSet* m_selectedDumpSet;
    std::map<QString, DumpSet*> m_openedDumpSets;

    QTreeWidgetItem* getDumpSetItem();
    //returns false if the closure was aborted by the user
    bool close(QTreeWidgetItem* item);
};

#endif // DUMPSETTREEWIDGET_H
