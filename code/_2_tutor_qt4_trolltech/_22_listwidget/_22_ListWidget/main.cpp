/*
 * A. QListWidget memo:
 *
 * 1. selectionMode()
 *  Determine how many items can be selected at the same time.
 *
 * 2. add QListWidgetItem to QListWidget
 *  - a. QListWidgetItem( QString str_content, QListWidget* listWidget);
 *  - b. listWidget->insertItem(int row, QListWidgetItem* newItem);
 *  - c. with multiple items:
 *      listWidget->insertItems(int start_row, QStringList list);
 *
 * 3. count()
 *  Return number items in list widget
 *
 * 4. currentItem() and setCurrentItem()
 *  - Current item can change by keyboard or clicking different item
 *      then emit signal currentItemChanged()
 *
 * ====================================
 * B. QListWidgetItem memo:
 *
 * By default a QListWidgetItem hold several pieaces of information.
 * - setText() -> setFont(), setForeground(), setBackground() and alignment
 *      by setTextAlignment()
 * - setIcon()
 * - setToolTip(), setStatusTip()
 * - By default, items are enabled, selectable, checkable, and can be
 *      the source of drag and drop operations.
 * - setHidden(), isHidden()
 *
 * Or using user custem type.
 *
 */



#include "mainwindow.h"

#include <QApplication>

#include <QListWidget>
#include <QListWidgetItem>  // is not a QObject, can copy

#include <QScrollBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    QListWidget* list_widget= new QListWidget(&w);
    w.setCentralWidget(list_widget);


    list_widget->setAlternatingRowColors(true);
    list_widget->setMouseTracking(true);

    for(int i = 0 ; i < 100 ; ++i)
    {
        QListWidgetItem* tmp_item = new QListWidgetItem();

        tmp_item->setText(QString::number(i));
        tmp_item->setToolTip(QString("Tool tip: Number ")+QString::number(i));
        tmp_item->setStatusTip(QString("Status tip: Number ")+QString::number(i));


        if(i%3) tmp_item->setIcon(QIcon(":/image/new.png"));
        else tmp_item->setIcon(QIcon(":/image/open.png"));

        list_widget->addItem(tmp_item);
    }


    w.show();
    return a.exec();
}
