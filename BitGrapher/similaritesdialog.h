#ifndef SIMILARITESDIALOG_H
#define SIMILARITESDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include "dumpset.h"

class SimilaritesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SimilaritesDialog(QWidget *parent = 0, DumpSet* ds = NULL, QString* selectedDump = NULL);
    // selectedDUmp : where the compared dump's name (the one to display) will be stored
    static std::list<std::pair<int,int> >* getSimilarities(DumpSet* ds, QString* selectedDump = NULL);
    Dump getDump1();
    Dump getDump2();
    int getMinSize();

signals:

public slots:
    void refreshDumps1();
    void refreshDumps2(const QString dump1 = "");
    void processAndClose();
    void cancelAndClose();

private:
    QString* m_selectedDump;
    DumpSet* m_dumpSet;
    QComboBox* m_dump1CB;
    QComboBox* m_dump2CB;
    QSpinBox* m_minSizeSpinBox;

    //the result is tored here, to be recovered after window closure
    static std::list<std::pair<int,int> >* m_result;

};

#endif // SIMILARITESDIALOG_H
