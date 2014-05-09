#ifndef ASSOCIATIONVIEWWIDGET_H
#define ASSOCIATIONVIEWWIDGET_H

#include <QWidget>
#include "core/Association.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <vector>

#include <string>
#include <iostream>

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


private:
    Ui::AssociationViewWidget *ui;
};

#endif // ASSOCIATIONVIEWWIDGET_H
