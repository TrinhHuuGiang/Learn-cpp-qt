
/*
 * Note:
 * - About Close event: https://doc.qt.io/qt-6.5/qwidget.html#closeEvent
 */

#include "_b_config_logic_layer_2.h"
#include "ui__b_config_logic_layer_2.h"

/* ==========================================================================
 * Code
-========================================================================== */

#define ICON_SVG_EXIT  ":/icon/rsrc/Icon/feather/x-square.svg"
#define ICON_SVG_DOWN  ":/icon/rsrc/Icon/feather/chevrons-down.svg"
#define ICON_SVG_SEND  ":/icon/rsrc/Icon/feather/send.svg"




/* ==========================================================================
 * Code
-========================================================================== */
_b__preview_and_config::_b__preview_and_config(
    const board_info_t& board_info_origin,
    const QString& final_json_str,
    QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::_b__preview_and_config)
    , board_info_origin(board_info_origin)
    , final_json_str(final_json_str)
{
    ui->setupUi(this);

    this->setWindowTitle("Preview configuration");

    //==========================Inform Config ================
    // set outline frame ( see example combinations F1)
    ui->frame_main->setFrameShape(QFrame::Box);
    ui->frame_main->setFrameShadow(QFrame::Sunken);
    ui->frame_main->setLineWidth(1);//ptx
    ui->frame_main->setMidLineWidth(3);


    // set preview frame ( see example combinations F1)
    ui->frame_preview->setFrameShape(QFrame::Box);
    ui->frame_preview->setFrameShadow(QFrame::Sunken);
    ui->frame_preview->setLineWidth(1);//ptx
    ui->frame_preview->setMidLineWidth(3);


    // button and label
    // set button/ label exit
    {
        QSize btn_exit_size = ui->btn_exit->size();
        btn_exit_size.setWidth(btn_exit_size.height()); // square

        ui->btn_exit->setStyleSheet(BTN_STYLE_DESIGN);

        ui->label_ic_exit->setPixmap(renderSvgToPixmap(ICON_SVG_EXIT
                                                       ,btn_exit_size));

    }

    // preview label
    {
        QSize label_prev_size = ui->label_preview->size();
        label_prev_size.setWidth(label_prev_size.height()); // square

        ui->label_ic_left_arrow->setPixmap(renderSvgToPixmap(ICON_SVG_DOWN
                                                       ,label_prev_size));
        ui->label_ic_right_arrow->setPixmap(renderSvgToPixmap(ICON_SVG_DOWN
                                                             ,label_prev_size));

    }


    // set button/ label send
    {
        QSize btn_send_size = ui->btn_send->size();
        btn_send_size.setWidth(btn_send_size.height()); // square

        ui->btn_send->setStyleSheet(BTN_STYLE_DESIGN);

        ui->label_ic_send->setPixmap(renderSvgToPixmap(ICON_SVG_SEND
                                                       ,btn_send_size));

    }


    qDebug()<<this<<"- Created window preview board configuration";
}

// destructor
_b__preview_and_config::~_b__preview_and_config()
{
        // emit preview_page_closed(); //<< wrong, never emit in destructor

    delete ui;

    qDebug()<<this<<"- Deleted window preview board configuration";
}



// close preview page, emit for config mode show
void _b__preview_and_config::on_btn_exit_clicked()
{
    // hide page before close
    this->hide();

    // emit show config page
    qDebug()<< "emit preview page closed";
    emit preview_page_closed();


    // delete later
    this->deleteLater();
    qDebug()<<this<<"- Window preview will delete later";
}


/*
 *  some time user click X instead of button exit
 *  - https://doc.qt.io/qt-6.5/qwidget.html#closeEvent
 *  - override closeEvent to handle when X is clicked
 */
void _b__preview_and_config::closeEvent(QCloseEvent *event)
{
    // emit show config page
    qDebug()<< "emit preview page closed";
    emit preview_page_closed();



    // never call deleteLater, qt will call it when
    // + event->accept or not set -> close normal
    // + if event->ignore  -> can't close -> close by taskmanager
    event->accept();
    // event->ignore();
}

