#include "showdialogtemplate.h"
#include "ui_showdialogtemplate.h"

// Qt
#include "QColor"

#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QProgressDialog>
#include <QMessageBox>
#include <QErrorMessage>

#include "QDebug"

// C
#include <cstring>
#include <cassert>

ShowDialogTemplate::ShowDialogTemplate(bool* init_done, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowDialogTemplate)
    , w_lst(nullptr)
{
// default return
    // bool ret = false;

    // ui
    ui->setupUi(this);
    ui->wnameLabel->setText("None");


#define S_WIDGET_LST_SIZE   7
    {
        QDialog* w_lst_tmp[S_WIDGET_LST_SIZE] =
            {
                new QColorDialog,
                new QFontDialog,
                new QFileDialog,
                new QInputDialog,
                new QProgressDialog,
                new QMessageBox,
                new QErrorMessage
            };


        for(int i = 0 ; i <S_WIDGET_LST_SIZE ; ++i )
            if(!w_lst_tmp[i])
            {
                // clean
                for(int j = 0 ; j <i ; ++j )
                {
                    delete(w_lst_tmp[j]); w_lst_tmp[j] = nullptr;
                }
                goto rvcl_false_1;
            }

        w_lst = new QDialog *[S_WIDGET_LST_SIZE];
        if(!w_lst)
        {
            // clean
            for(int i = 0 ; i <S_WIDGET_LST_SIZE ; ++i )
            {delete(w_lst_tmp[i]); w_lst_tmp[i] = nullptr;}

            goto rvcl_false_1;
        }
        std::memcpy(w_lst, w_lst_tmp, S_WIDGET_LST_SIZE*sizeof(w_lst_tmp[0]));
    }



// Test show -> hide . default all dialog is exit.

    for (int i = 0 ; i < S_WIDGET_LST_SIZE; ++i)
    {
        w_lst[i]->show();
        w_lst[i]->hide();
    }


// default return
    goto rvcl_done;

// REVERSE CLEAN

rvcl_false_1:
    *init_done=false;
    //clean init value
    delete ui; ui=nullptr;
    return;

rvcl_done:
    *init_done = true;
    qDebug()<<"show dialog Construct done";
    return;
}

ShowDialogTemplate::~ShowDialogTemplate()
{
    if(ui) delete ui;

    if(w_lst)
    {
        for(int i = 0 ; i < S_WIDGET_LST_SIZE; i++)
        {
            delete w_lst[i];
            qDebug()<<"show dialog Delete ["<< i <<"] done";
        }
        delete[] w_lst; w_lst = nullptr;

    }

    qDebug()<<"show dialog Destruct done";
}

void ShowDialogTemplate::show_first_dialog(int* cur_index)
{
    int current_id = 0;

    if(!w_lst) return;

    // update current index
    *cur_index = current_id;

    // show
    ((w_lst[current_id]))->show();

    return;
}

void ShowDialogTemplate::show_next_dialog(int* cur_index)
{
    int current_id = *cur_index;
    int next_id = 0;

    if(!w_lst) return;

    if(current_id <0 || current_id >= S_WIDGET_LST_SIZE)
    {
        // reset index
        next_id = 0;
    }
    else
    {
        if(current_id + 1 == S_WIDGET_LST_SIZE)
        {next_id = 0;}
        else
        {
            next_id = current_id+1;
        }
    }

    // update current index
    *cur_index = next_id;

    // hide old, show new
    ((w_lst[current_id]))->hide();
    ((w_lst[next_id]))->show();

    return;
}
