#ifndef DUMPCOMBOBOX_H
#define DUMPCOMBOBOX_H

#include <QComboBox>
#include "../core/Dump.h"

/// \class DumpComboBox
///
/// \brief A ComboBox that selects Dumps and has an index.
///
/// \author Gabriel Prevosto
///
/// \date 23/05/2014

class DumpComboBox : public QComboBox
{
    Q_OBJECT
public:

    /// \brief A constructor fot DumpComboBox
    /// \param parent The parent Widget (optional).
    /// \param index The ComboBox's index.
    explicit DumpComboBox(QWidget *parent = 0, int index = 0);

    /// \brief Sets the selectable Dumps.
    /// \param dumps The list of Dumps that will be selectable.
    void setDumpList(std::vector<Dump const*> dumps);

    /// \brief Returns a pointer to the selected Dump.
    /// \returns A pointer to the selected Dump.
    Dump const* currentDump();

signals:

    /// \brief Emitted when the selected item changes.
    /// \param i The ComboBox's index.
    void currentDumpChanged( int i );

private slots:

    /// \brief Call this when the current index changed.
    /// \note This is used to trigger currentDumpChanged.
    void onCurrentIndexChanged();

private:
    int m_index; ///< The ComboBox's index.
    std::vector<Dump const*> m_dumps; ///< The Dumps that can be selected

};

#endif // DUMPCOMBOBOX_H
