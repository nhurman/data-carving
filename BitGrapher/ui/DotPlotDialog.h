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
    const Dump* getDump(int index);

    /// \brief Getter for the minimum size
    /// \return the minimum diagonal size
    int getMinSize() const;

    /// \brief Getter for m_result
    /// \return the DotPlotResult resulting from the execution of this dialog
    DotPlotResult* getResult() const;

signals:

public slots:
    /// \brief Call this when a comboBox's selection has changed. Prevents the selection of a same Dump twice.
    /// \param modifiedIndex Index of the modified ComboBox. -1 to refresh all.
    void refreshComboBoxes(int modifiedIndex);

    /// \brief Call this when the user presses OK (runs the algorithm and closes the dialog).
    void processAndClose();

    /// \brief Call this when the user presses Cancel (closes the dialog).
    void cancelAndClose();

    /// \brief Call this when the user presses the default button (Sets the size to its preferred value).
    /// \note Uses preferredStringSize().
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
