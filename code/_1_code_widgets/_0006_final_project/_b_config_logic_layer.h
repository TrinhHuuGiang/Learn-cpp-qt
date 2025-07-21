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

#ifndef _B_CONFIG_LOGIC_LAYER_H
#define _B_CONFIG_LOGIC_LAYER_H

/* =============================================================
 * Purpose:
 *  - Manage HTTP communication with the ESP32 board (default IP: 192.168.1.1)
 *
 * Functional Flow:
 * 1. Send HTTP GET request to /get_board_type (expecting plain text)
 *    - Use QPointer to track this page's life status:
 *        + If QPointer == nullptr -> page was deleted → return immediately
 *        + If signal send failed -> retry connection
 *        + If signal send succeeded:
 *            -> parse board type
 *            -> query database for matching logic blocks code
 *            -> update combobox with results
 *
 * 2. Reset session:
 *    - To renew state, return to main page then re-enter this page
 *    - Advantage: cleans old session, simpler to manage
 *
 * 3. Calculate availability before adding to wishlist:
 *    - If the board has capacity → allow addition
 *    - If the board is full → show warning message
 *
 * 4. Send configuration to board:
 *    - Step 1: Send HTTP GET to /ready_to_config → wait for board to enter config mode
 *    - Step 2: Send HTTP POST with JSON config data
 * ============================================================= */




/* =============================================================
 * Definitions
============================================================= */
#include <QWidget>
#include <QObject>

#include <QTimer>
#include <QString>
#include <QList>

// File JSON
#include <QJsonDocument>
#include <QJsonObject> // When there is distinguishable content between objects,
                    // and it has to short for string compare
                    // using them as keys will make searching faster.
#include <QJsonArray>  // When there is no unique key between objects,
                    // or unique string verylog
                    //using an array is better for browsing because it has an index for each object.


// HTTP
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>


#include "z_widget_style.h"
#include "z_global_db_connect.h"

#include "_1_menuconfig.h"

#include "rsrc_code/http_path/_http_path.h"

typedef struct
{
    QString b_code;
    QString b_desc;
    QString h_limit;
} board_info_t;

typedef struct
{
    QString lg_code;
    QString lg_desc;
    QString h_require;
} lg_info_t;


#include "_b_config_logic_layer_2.h"



/* =============================================================
 * Classes
============================================================= */
namespace Ui {
class _b_config_logic_layer;
}

class _b_config_logic_layer : public QWidget
{
    Q_OBJECT

public:

    explicit _b_config_logic_layer(QWidget *parent = nullptr);
    ~_b_config_logic_layer();


private:

    void try_get_list_logic_block_available();

    int check_board_available_before_add_block_to_wishlist();


private slots:
    void try_connect_to_dev_board();

    void on_btn_back_clicked();//back to menu

    void on_btn_add_wishlist_clicked();

    void on_combox_list_avail_currentIndexChanged(int index);

    void on_combox_list_order_currentIndexChanged(int index);

    void on_btn_rm_order_clicked();

    void on_btn_start_cf_clicked();


    void try_show_this_page_if_hide();

private:
    Ui::_b_config_logic_layer *ui;

    QNetworkAccessManager * http_manager;

    board_info_t board_info;

    QList<lg_info_t> output_list;

    QList<lg_info_t> wish_list;

    int reconn_count;

};

#endif // _B_CONFIG_LOGIC_LAYER_H
