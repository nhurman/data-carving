#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define DEFAULT_DIRECTORY "../Utils/TestFiles"

#include <QMainWindow>
#include <QListWidgetItem>
#include "bitstring.h"
#include "dumpset.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::MainWindow *ui;
    BitString *m_bitstring;
    DumpSet m_dumpSet;
    //refreshes the display of the bitsrting
    void refreshDisplay();
};

#endif // MAINWINDOW_H
