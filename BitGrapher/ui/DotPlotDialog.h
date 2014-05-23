#ifndef DOTPLOTDIALOG_H
#define DOTPLOTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include "core/DumpSet.h"
#include "ui/DumpComboBox.h"
#include "algorithms/DotPlotResult.h"
namespace Ui {
class DotPlotDialog;
}

class DotPlotDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DotPlotDialog(QWidget *parent = 0, DumpSet* ds = NULL, QString* selectedDump = NULL);
    // selectedDump : where the compared dump's name (the one to display) will be stored
    //static Similarities* getSimilarities(DumpSet* ds, QString* selectedDump = NULL);
    Dump getDump(int index);
    int getMinSize() const;
    DotPlotResult* getResult() const;

signals:

public slots:
    void refreshComboBoxes(int modifiedIndex); //modifiedIndex : index of the modified CB -1 to refresh all
    void processAndClose();
    void cancelAndClose();
    void displayDefaultSize();

private:
    QVBoxLayout* m_layout;
    DumpSet* m_dumpSet;
    QString* m_selectedDump;
    std::vector<DumpComboBox*> m_dumpCBs;
    QSpinBox* m_minSizeSpinBox;

    void refreshComboBox(int index);
    int preferredStringSize();

    //the result is stored here, to be recovered after window closure
    static DotPlotResult* m_result;

};

#endif // DOTPLOTDIALOG_H
