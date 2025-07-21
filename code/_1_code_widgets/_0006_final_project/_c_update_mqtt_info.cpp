/*
    Copyright (C) 2025  Giang Trinh

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* ==========================================================================
 * list object
 *  - label_ic_back
 *  - btn_back
 *
 *  - ledit_link_broker
 *  - btn_getcert_broker
 *
 *  - label_ic_unk_broker
 *  - label_unk_broker
 *
 *  - ledit_username
 *  - ledit_password
 *
 *  - label_status_log
 *
 *  - label_ic_update
 *  - btn_update
 *
========================================================================== */



/* ==========================================================================
 * Definition
========================================================================== */

#include "_c_update_mqtt_info.h"
#include "ui__c_update_mqtt_info.h"

#define ICON_SVG_MESSAGE ":/icon/rsrc/Icon/feather/twitch.svg"

#define ICON_SVG_BACK ":/icon/rsrc/Icon/feather/arrow-left.svg"






/* ==========================================================================
 * Class
========================================================================== */
_c_update_mqtt_info::_c_update_mqtt_info(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::_c_update_mqtt_info)
{
    ui->setupUi(this);
    this->setWindowTitle("Update mqtt information");



    //==========================Style ================
    // set frame functions list ( see example combinations F1)
    ui->mqtt_frame->setFrameShape(QFrame::Box);
    ui->mqtt_frame->setFrameShadow(QFrame::Sunken);
    ui->mqtt_frame->setLineWidth(1);//ptx
    ui->mqtt_frame->setMidLineWidth(3);


    // set button/label net
    ui->pushButton->setStyleSheet(BTN_STYLE_DESIGN);

    QSize lb_icon_unk_size;
    lb_icon_unk_size.setHeight(MAIN_APP_DEFAULT_FONT_SIZE); // height
    lb_icon_unk_size.setWidth(MAIN_APP_DEFAULT_FONT_SIZE); // width

    ui->label_ic_unk_broker->setPixmap(renderSvgToPixmap(ICON_SVG_MESSAGE
                                                     ,lb_icon_unk_size));


    // set button back
    QSize btn_back_size = ui->btn_back->size();
    btn_back_size.setWidth(btn_back_size.height()); // square

    ui->btn_back->setStyleSheet(BTN_STYLE_DESIGN);

    ui->label_ic_back->setPixmap(renderSvgToPixmap(ICON_SVG_BACK
                                                   ,btn_back_size));



    qDebug()<<this<<"- created window mqtt inform";

}



_c_update_mqtt_info::~_c_update_mqtt_info()
{
    delete ui;

    qDebug()<<this<<"- deleted window mqtt inform";
}




void _c_update_mqtt_info::on_btn_back_clicked()
{
    // hide this window
    this->hide(); // no continue click, smooth when switch window

    // return menu page

    qDebug() << this << "Returning menu page";

    _1_menuconfig * menu_page = new(std::nothrow) _1_menuconfig(nullptr); // nothow -> return nullptr if fail

    if(menu_page)
    {
        menu_page->show();
        qDebug() << this << "Created menu page";
    }
    else
    {
        qDebug() << this << "Failed when allocate menu_page";
        qDebug() << this << "Force quit app!!!";
        QApplication::quit();
    }

    // safe close by add delete command to last of queue exec loop
    this->deleteLater();
}

