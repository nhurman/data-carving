#ifndef DUMPCOMBOBOX_H
#define DUMPCOMBOBOX_H

#include <QComboBox>

/// \class DumpComboBox
///
/// \brief A ComboBox that selects items (e.g. Dumps) while keeping track of the selected index.
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
    /// \param index The index of the Dump selected by default. 0 by default.
    explicit DumpComboBox(QWidget *parent = 0, int index = 0);

signals:

    /// \brief Emitted when the selected item changes.
    /// \param i The index of the new selected item.
    void currentDumpChanged( int i );

private slots:

    /// \brief Call this when the current index changed.
    /// \note This is used to trigger currentDumpChanged.
    void onCurrentIndexChanged();

private:
    int m_index; ///< The index of the selected item.

};

#endif // DUMPCOMBOBOX_H
