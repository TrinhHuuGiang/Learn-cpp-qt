#include "bi_widgets.h"

#include <QApplication>

#include <QLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


// Widgets test
    Dialog w;

    // w.layout()->setSizeConstraint(QLayout::SetFixedSize);
    int w_width_hint = w.sizeHint().width() * 8 / 10;
    w.setFixedWidth(w_width_hint ? w_width_hint : 1 );
    int w_height_hint = w.sizeHint().height() * 8 / 10;
    w.setFixedHeight(w_height_hint ? w_height_hint : 1 );

    w.show();



// Dialog template
    Dialog w1;
    w1.show();

    return a.exec();
}
