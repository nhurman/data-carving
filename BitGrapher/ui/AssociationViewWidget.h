#ifndef ASSOCIATIONVIEWWIDGET_H
#define ASSOCIATIONVIEWWIDGET_H

#include <QMap>
#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <QFileDialog>
#include <QTextStream>
#include <QTableWidget>

#include "core/Label.h"
#include "encoding/Encoding2.h"

/// \class AssociationViewWidget
///
/// \brief Panel that show masks
///
/// \author Gaugry Thierry
///
/// \date 24/05/2014

class AssociationViewWidget : public QTableWidget
{
    Q_OBJECT

public:
    /// \brief Constructor for AssociationViewWidget.
    /// \param parent The parent Widget (optional).
    explicit AssociationViewWidget(QWidget *parent = 0);

    /// \brief Destructor for AssociationViewWidget.
    ~AssociationViewWidget();

    /// \brief Create a new line above the selected line.
    void newLine();

    /// \brief Delete selected line.
    void deleteLine();

    /// \brief Allow user to select a mask (*.mk) to open.
    /// \note Will close current mask.
    void openMask();

    /// \brief Allow user to save a mask (*.mk) at chosen location (open a dialog).
    bool saveMaskAs();

    /// \brief Allow user to save a mask (*.mk) at m_filePath location.
    /// \note Call saveMaskAs if m_filePath == NULL.
    bool saveMask();

    /// \brief Close current mask (*.mk).
    bool closeMask();

    /// \brief Open a dialog to add a new line in the association view (*.mk).
    bool newLabelDialog();

    Label getLabel(int row);
    void setBitString(BitString const* bs);
    QMap<QString, Encoding2*>* getEncodings();

public slots:
    void addLabel(Label l);
    void updateLabel(int row, Label l);


private:
    QString m_filePath; ///< Path to the mask (for saving)
    QMap<QString, Encoding2*> m_encodings;
    BitString const* m_bitString;
};

#endif // ASSOCIATIONVIEWWIDGET_H
