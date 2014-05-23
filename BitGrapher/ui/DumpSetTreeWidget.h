#ifndef DUMPSETTREEWIDGET_H
#define DUMPSETTREEWIDGET_H

#include <QTreeWidget>
#include <QMessageBox>
#include <QFileDialog>

#include "core/Dump.h"
#include "core/DumpSet.h"

/// \class DumpSetTreeWidget
///
/// \brief Widget used to open, select, save and close Dumps and DumpSets.
///
/// \note To make it movable, stick it in a DockWidget.
///
/// \author Gabriel Prevosto
/// \author Nicolas Hurman
///
/// \date 23/05/2014

class DumpSetTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:

    /// \brief Constructor for DumpSetTreeWidget.
    /// \param parent The parent Widget (optional).
    explicit DumpSetTreeWidget(QWidget *parent = 0);

    /// \brief Getter for m_selectedDump.
    /// \return The current Dump.
    Dump const* getCurrentDump();

    /// \brief Getter for m_selectedDumpSet.
    /// \return The current DumpSet.
    DumpSet* getCurrentDumpSet();

    /// \brief Saves the current DumpSet.
    void saveDumpSet();

    /// \brief Saves the current DumpSet as... (the new name will be chosen by the user)
    void saveDumpSetAs();

    /// \brief Opens a DumpSet (chosen by the user).
    void openDumpSet();

signals:

    /// \brief Emitted when the selected Dump changes.
    /// \param The new selection.
    void selectedDumpChanged(Dump const*);

    /// \brief Emitted when the selected DumpSet changes.
    /// \param The new selection
    void selectedDumpSetChanged(DumpSet*);

    /// \brief Emitted when the user asked to saved the DumpSet.
    /// \param The DumpSet to be saved.
    void dumpSetNeedsSaving(DumpSet*);

public slots:

    /// \brief Opens a given DumpSet.
    /// \param ds The DumpSet to add.
    void addDumpSet(DumpSet* ds);

    /// \brief Adds a Dump to the current DumpSet.
    /// \param filePath The path to the Dump's file.
    /// \param format The input format for the file. RAW by default.
    void addDump(QString filePath, InputFormat format = RAW);

    /// \brief Call this when the current item changed.
    /// \param current The new selected item.
    /// \param previous The old selected item.
    /// \note This is used to trigger selectedDumpChanged and selectedDumpSetChanged.
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    /// \brief Closes the current DumpSet.
    /// \return Set to false if the closure was aborted by the user.
    /// \note If there are any unsaved changes, the user will be asked to either save them, discard them or cancel the closure.
    bool closeDumpSet();

    /// \brief Removes the current Dump from its DumpSet.
    void removeDump();

    /// \brief Closes all DumpSets.
    /// \return Set to false if the closure was aborted by the user.
    /// \note If there are any unsaved changes, the user will be asked to either save them, discard them or cancel the closure.
    bool closeAll();

private:
    typedef std::map<DumpSet*, std::map<QTreeWidgetItem*, Dump const*>> DumpSetMap; ///< Type used to sort Dumps and TreeWidgetItems by DumpSet.

    int m_nbNewDumpSets; ///< Number used to name new DumpSets.
    DumpSet* m_selectedDumpSet; ///< The DumpSet that is currently selected.
    Dump const* m_selectedDump; ///< The Dump that is currently selected.
    std::map<QTreeWidgetItem*, DumpSet*> m_dumpSets; ///< The DumpSets corresponding to the items from the TreeWidget.
    DumpSetMap m_dumps; ///< The Dumps from each DumpSet and their respective items (from the TreeWidget).

    /// \brief Gets the item corresponding to the current DumpSet.
    /// \return The item corresponding to the current DumpSet.
    QTreeWidgetItem* getDumpSetItem();

    /// \brief Closes the DumpSet corresponding to the given item.
    /// \param item the item corresponding to the DumpSet to close.
    /// \return Set to true if the closure succeeded.
    bool close(QTreeWidgetItem* item);
};

#endif // DUMPSETTREEWIDGET_H
