#include <QApplication>
#include <QLayout>
#include <QDebug>

#include "bi_widgets.h"
#include "showdialogtemplate.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


// Widgets test
    Dialog w;

    // w.layout()->setSizeConstraint(QLayout::SetFixedSize);
    int w_width_hint = w.sizeHint().width() * 5 / 10;
    w.setFixedWidth(w_width_hint ? w_width_hint : 1 );
    // int w_height_hint = w.sizeHint().height() * 5 / 10;
    // w.setFixedHeight(w_height_hint ? w_height_hint : 1 );

    w.show();



// Dialog template
    bool init_done = false;

    ShowDialogTemplate w_showdialog = ShowDialogTemplate(&init_done);
    qDebug() << "Show Dialog init ret code: [" << init_done <<"]";

    w_showdialog.show();



    return a.exec();
}
