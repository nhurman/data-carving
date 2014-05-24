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

/// \class DotPlotDialog
///
/// \brief Dialog that appears to select the dumps and the minimum string size for a DotPlot operation
///
/// \author Gabriel Prevosto
/// \author Alexandre Audinot
///
/// \date 23/05/2014

class DotPlotDialog : public QDialog
{
    Q_OBJECT
public:
    /// \brief Constructor for DotPlotDialog.
    /// \param parent The parent Widget (optional).
    /// \param ds DumpSet from which to choose for the DotPlot operation
    explicit DotPlotDialog(QWidget *parent = 0, DumpSet* ds = NULL, QString* selectedDump = NULL);

    /// \brief Getter for m_dumpSet
    /// \param index index of the dump to get
    /// \return the dump at the given position
    Dump getDump(int index);

    /// \brief Getter for the minimum size
    /// \return the minimum diagonal size
    int getMinSize() const;

    /// \brief Getter for m_result
    /// \return the DotPlotResult resulting from the execution of this dialog
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
