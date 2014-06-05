#ifndef SIMILARITIESDIALOG_H
#define SIMILARITIESDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include "core/DumpSet.h"
#include "algorithms/Similarities.h"
#include "ui/DumpComboBox.h"

/// \class SimilaritiesDialog
///
/// \brief Dialog used to ask the user the parameters for the Similarities alogorithm.
///
/// \author Gabriel Prevosto
///
/// \date 24/05/2014

class SimilaritiesDialog : public QDialog
{
    Q_OBJECT
public:

    /// \brief Constructor for SimilaritiesDialog.
    /// \param parent The parent Widget (optional).
    /// \param ds The DumpSet in which the algorithm will be applied.
    /// \param selectedDump Where the compared dump (the one to display) will be stored.
    explicit SimilaritiesDialog(QWidget *parent = 0, DumpSet* ds = NULL, const Dump **selectedDump = NULL);

    /// \brief Displays the SimilaritiesDialog and returns the results of the algorithm.
    /// \note For an easy use of this class, just use this method.
    /// \param ds The DumpSet in which the algorithm will be applied.
    /// \param selectedDump Where the compared dump (the one to display) will be stored.
    /// \return An instance of Similarity with the results of the algorithm.
    static Similarities* getSimilarities(DumpSet* ds, Dump const** selectedDump = NULL);

    /// \brief Finds the dump selected by the ComboBox with the given index.
    /// \param index The index of the ComboBox to look at.
    /// \return The dump selected by the ComboBox with the index index.
    const Dump *getDump(int const index) const;

    /// \brief Gets the chosen minimum string size.
    /// \return The minimum string size.
    int getMinSize() const;

signals:

public slots:

    /// \brief Call this when a comboBox's selection has changed. Prevents the selection of a same Dump twice.
    /// \param modifiedIndex Index of the modified ComboBox. -1 to refresh all.
    void refreshComboBoxes(int modifiedIndex);

    /// \brief Call this when the user presses OK (runs the algorithm and closes the dialog).
    void processAndClose();

    /// \brief Call this when the user presses Cancel (closes the dialog).
    void cancelAndClose();

    /// \brief Call this when the user presses + (adds a ComboBox if possible).
    void addComboBox();

    /// \brief Call this when the user presses - (removes a ComboBox if possible).
    void removeComboBox();

    /// \brief Call this when the user presses the default button (Sets the size to its preferred value).
    /// \note Uses preferredStringSize().
    void displayDefaultSize();

private:
    QVBoxLayout* m_layout; ///< The layout ofr this Dialog.
    Dump const** m_selectedDump; ///< The Dump selected by the first ComboBox
    DumpSet* m_dumpSet; ///< The working DumpSet
    std::vector<DumpComboBox*> m_dumpCBs; ///< The ComboBoxes
    QSpinBox* m_minSizeSpinBox; ///< The SpinBox that controls the minimum string size

    /// \brief refreshes a single ComboBox.
    /// \param index The index of the ComboBoox to refresh.
    /// \note Used by refreshComboBoxes(int).
    void refreshComboBox(int const index);

    /// \brief Processes the preferred minimum string size.
    /// \return The preferred minimum string size.
    int preferredStringSize() const;

    static Similarities* m_result; ///< The result of the algorithm is stored here, to be recovered after window closure.
};



#endif // SIMILARITIESDIALOG_H
