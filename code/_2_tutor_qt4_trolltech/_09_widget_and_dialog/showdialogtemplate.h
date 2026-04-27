#ifndef SHOWDIALOGTEMPLATE_H
#define SHOWDIALOGTEMPLATE_H

#include <QDialog>


namespace Ui {
class ShowDialogTemplate;
}

class ShowDialogTemplate : public QDialog
{
    Q_OBJECT

public:
    explicit ShowDialogTemplate(bool* init_done, QWidget *parent = nullptr);
    ~ShowDialogTemplate();

    void show_first_dialog(int* cur_index);
    void show_next_dialog(int* cur_index);

private:
    Ui::ShowDialogTemplate *ui;
    QDialog** w_lst;
};

#endif // SHOWDIALOGTEMPLATE_H
