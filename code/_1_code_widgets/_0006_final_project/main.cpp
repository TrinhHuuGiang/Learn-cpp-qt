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
 * Note:
 * - Window:
 *  + Welcome (_1_config_window):
 *      ~ Login HiveMQ server
 *          + connect to HiveMQ server, parse info and
 *              implement interactive interface with database
 *
 *      ~ Update Http Logic Block:
 *          + with database, implement interface choose logic
 *              block setup for esp32 board
 *
 *      ~ Wifi config
 *          * http get:  get a list wifi from esp32
 *          * http post: ^ post feedback wifi info set into esp32
 *                       ^ then get feedback ok, restart wifi esp32
 *
 *      ~ MQTT config Hivemq broker info
 *          * new cert pem
 *          * username, password, broker uri
 *
 * - Resource:
 *  + icon get from: https://feathericons.com/
 *  + font style Roboto: https://fonts.google.com/specimen/Roboto
 *  + OpenSSL for android: https://doc.qt.io/qt-6.5/android-openssl-support.html
 *
 * - Tools
 *  + database manager: SQLite Studio
 *
========================================================================== */

/* ==========================================================================
 * Definition
========================================================================== */
#include <QApplication>

// Common QLibs
#include <QFontDatabase>            // set global font
#include <QFont>
#include <QString>
#include <QDebug>

// window app
#include "_1_menuconfig.h"

#include "_a_login_to_broker.h"
#include "_b_config_logic_layer.h"
#include "_b_config_logic_layer_2.h"
#include "_c_update_mqtt_info.h"
#include "_d_update_wifi_info.h"


// define
#include "z_widget_style.h"
#include "z_global_db_connect.h"


/* ==========================================================================
 * Main
========================================================================== */
int main(int argc, char *argv[])
{
    // main variable
    QApplication a(argc, argv);

    qDebug() << "app version: ["<<APP_VERSION<<"]";

//======================================= App config

    // set default app font
    int font_default = QFontDatabase::addApplicationFont(MAIN_APP_DEFAULT_REGULAR_FONT);
    QString family = QFontDatabase::applicationFontFamilies(font_default).at(0);
    QFont font(family, MAIN_APP_DEFAULT_FONT_SIZE);

    a.setFont(font); // set default application font
                    // Do not use this function in conjunction with Qt Style Sheets.


    // set default setStyleSheet is safe if not set font style
    // scroll bar style (QScrollArea Widget)
    a.setStyleSheet(SCROLLBAR_SIZE_DESIGN);



//======================================= Page config

    // WARNING: extremely serious error
    /*
     *  _1_menuconfig w_menu; //<< if use deleteLater() in object not dynamic
     *                      // program will crash because deleta a stack
     *                      // ONLY use method normal declare in test
     *  w_menu.show();
    */

    // show menuconfig window
    // _1_menuconfig* w_menu = new _1_menuconfig(nullptr);
    // w_menu->show();


    // // // login to mqtt server
    // _a_login_to_broker w_login;
    // w_login.show();



    //config board logic blocks
    _b_config_logic_layer* w_config_lg_layer = new _b_config_logic_layer;
    w_config_lg_layer->show();


    //preview config before send
    // board_info_t test_board_info_origin;
    // QString test_final_json_str;
    // _b__preview_and_config* w_preview_config_board =
    //     new _b__preview_and_config(test_board_info_origin,test_final_json_str);
    // w_preview_config_board->show();



    // // update mqtt inform
    // _c_update_mqtt_info w_update_mqtt_info;
    // w_update_mqtt_info.show();


    // // update wifi inform
    // _d_update_wifi_info w_update_wifi_info;
    // w_update_wifi_info.show();


//======================================= Main loop

    // loop
    return a.exec();
}
