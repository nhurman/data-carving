#ifndef SIMILARITESDIALOG_H
#define SIMILARITESDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include "core/dumpset.h"
#include "algorithms/similarities.h"
#include "ui/dumpcombobox.h"

class SimilaritesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SimilaritesDialog(QWidget *parent = 0, DumpSet* ds = NULL, QString* selectedDump = NULL);
    // selectedDump : where the compared dump's name (the one to display) will be stored
    static Similarities* getSimilarities(DumpSet* ds, QString* selectedDump = NULL);
    Dump getDump(int index);
    int getMinSize();

signals:

public slots:
    void refreshComboBoxes(int modifiedIndex); //modifiedIndex : index of the modified CB -1 to refresh all
    void processAndClose();
    void cancelAndClose();
    void addComboBox();
    void removeComboBox();

private:
    QVBoxLayout* m_layout;
    QString* m_selectedDump;
    DumpSet* m_dumpSet;
    std::vector<DumpComboBox*> m_dumpCBs;
    QSpinBox* m_minSizeSpinBox;

    void refreshComboBox(int index);

    //the result is tored here, to be recovered after window closure
    static Similarities* m_result;
};



#endif // SIMILARITESDIALOG_H
