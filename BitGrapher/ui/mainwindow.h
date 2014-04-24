#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core/Dump.h"
#include "BitmapWidget.h"
#include "HexViewWidget.h"
#include "TextViewWidget.h"

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
    void on_selectedDumpChanged(Dump const* ds);

    void on_actionAdd_dump_triggered();
    void on_actionNew_set_triggered();
    void on_actionRemove_dump_triggered();
    void on_actionClose_set_triggered();
    void on_actionOpen_set_triggered();
    void on_actionSave_set_triggered();
    void on_actionSave_set_as_triggered();
    void on_actionBitmap_triggered();

    void on_actionHexadecimal_triggered();

    void on_actionText_triggered();

private:
    Ui::MainWindow *ui;
    BitmapWidget* m_bitmap;
    HexViewWidget* m_hexView;
    TextViewWidget* m_textView;
};

#endif // MAINWINDOW_H
