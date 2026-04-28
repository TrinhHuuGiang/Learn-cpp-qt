#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Main window UI
#include <QMainWindow>

// Custom window, ui
#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"

// Custom libs
#include "spreadsheet.h"

// Qt lib
#include <QString>
#include <QAction>
#include <QMenu>
#include <QToolBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//========== Chunk 1 =========
protected:
    void closeEvent(QCloseEvent *event) override;

//========== Chunk 2 =========
private slots:
    void newFile();


//========== Chunk 3 =========
private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    // void createStatusBar();

private:
    Ui::MainWindow *ui;

    // Action
    QAction *newAction;

    // Menu
    QMenu *fileMenu;

    // Toolbar
    QToolBar* fileToolBar;
    QToolBar* editToolBar;
};
#endif // MAINWINDOW_H
