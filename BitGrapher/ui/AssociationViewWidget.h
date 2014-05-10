#ifndef ASSOCIATIONVIEWWIDGET_H
#define ASSOCIATIONVIEWWIDGET_H

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

#include "ui_AssociationViewWidget.h"

#include "core/Association.h"


namespace Ui {
class AssociationViewWidget;
}

class AssociationViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AssociationViewWidget(QWidget *parent = 0);
    ~AssociationViewWidget();

private slots:
    void newLine();
    void deleteLine();
    void openMask();
    bool saveMaskAs();
    bool saveMask();
    bool closeMask();



private:
    Ui::AssociationViewWidget *ui;
    QString m_filePath;
};

#endif // ASSOCIATIONVIEWWIDGET_H
