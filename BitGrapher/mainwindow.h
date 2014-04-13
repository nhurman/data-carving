#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define DEFAULT_DIRECTORY "../Utils/TestFiles"

#define DISSIM_COLOR "red"
#define SIM_COLOR "green"
#define DEFAULT_COLOR "black"

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include "bitstring.h"
#include "dumpset.h"
#include "encoding.h"

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
    // File Menu
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();

    // View Menu
    void on_actionDiagonals_View_triggered();
    void on_actionBitmap_View_triggered();

    // Others
    void on_actionAdd_Dump_to_Set_triggered();

    void on_actionNew_Dump_Set_triggered();

    void on_treeWidget_selectedDumpSetChanged(DumpSet *);

    void on_treeWidget_selectedDumpChanged(Dump);

    void on_actionClose_triggered();

    void on_actionSimilarities_triggered();

    void on_actionEncodings_triggered();

    void on_actionExit_triggered();

    //returns false if the closure was aborted by the user
    bool on_actionClose_all_triggered();

    void saveDumpSet(DumpSet* ds);

    void saveDumpSetAs(DumpSet* ds);

private:
    Ui::MainWindow *ui;
    BitString *m_bitstring;
    DumpSet* m_dumpSet;

    //refreshes the display of the bitsrting
    void refreshDisplay();
};

#endif // MAINWINDOW_H
