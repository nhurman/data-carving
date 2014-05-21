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
#include <QTableWidget>



class AssociationViewWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit AssociationViewWidget(QWidget *parent = 0);
    ~AssociationViewWidget();
    void newLine();
    void deleteLine();
    void openMask();
    bool saveMaskAs();
    bool saveMask();
    bool closeMask();
    bool newLabelDialog();




private:
    QString m_filePath;
};

#endif // ASSOCIATIONVIEWWIDGET_H
