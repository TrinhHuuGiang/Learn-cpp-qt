#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QCloseEvent;

class QThread;
class work_Manager;

class QMessageBox;

class animation_Widget;

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

signals:
    void request_end_to_manager();

private slots:
    /*
     * It may long blocking while waiting manager thread end
     */
    void closeEvent(QCloseEvent* event);

    void onManagerFinished();

private:
    Ui::MainWindow *ui;

    QThread* thread_manager;
    work_Manager* work_manager;

    QMessageBox* msgbox_closing;
    bool close_safe = false;


private:
    animation_Widget *animWidget;

};
#endif // MAINWINDOW_H
