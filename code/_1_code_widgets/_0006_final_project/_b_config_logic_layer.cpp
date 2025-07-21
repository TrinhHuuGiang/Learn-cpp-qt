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
 *  - combox_list_avail
 *
 *  - btn_add_wishlist
 *  - label_ic_add_wishlist
 *
 *  - label_stat_select
 *
 *  - combox_list_order
 *
 *  - label_logic_if_log
 *
 *  - btn_rm_order
 *  - label_ic_rm_order
 *
 *  - btn_start_cf_ic
 *  - btn_start_cf
========================================================================== */



/* ==========================================================================
 * Definition
========================================================================== */


#include "_b_config_logic_layer.h"
#include "ui__b_config_logic_layer.h"

#define ICON_SVG_BACK ":/icon/rsrc/Icon/feather/arrow-left.svg"
#define ICON_SVG_ADD_WISH ":/icon/rsrc/Icon/feather/thumbs-up.svg"
#define ICON_SVG_RM_WISH  ":/icon/rsrc/Icon/feather/thumbs-down.svg"
#define ICON_SVG_START_CF ":/icon/rsrc/Icon/feather/tool.svg"



/* ==========================================================================
 * Class
========================================================================== */
_b_config_logic_layer::_b_config_logic_layer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::_b_config_logic_layer)
    , reconn_count(0)
{
    ui->setupUi(this);
    this->setWindowTitle("Setup logic blocks to board");

    //==========================Inform Config ================
    // set frame functions list ( see example combinations F1)
    ui->frame_cf_lgb->setFrameShape(QFrame::Box);
    ui->frame_cf_lgb->setFrameShadow(QFrame::Sunken);
    ui->frame_cf_lgb->setLineWidth(1);//ptx
    ui->frame_cf_lgb->setMidLineWidth(3);

    // button and label
    // set button/ label back
    {
        QSize btn_back_size = ui->btn_back->size();
        btn_back_size.setWidth(btn_back_size.height()); // square

        ui->btn_back->setStyleSheet(BTN_STYLE_DESIGN);

        ui->label_ic_back->setPixmap(renderSvgToPixmap(ICON_SVG_BACK
                                                       ,btn_back_size));

    }

    // btn_add_wishlist
    // label_ic_add_wishlist
    {
        QSize btn_wishlist_size = ui->btn_add_wishlist->size();
        btn_wishlist_size.setWidth(btn_wishlist_size.height()); // square

        ui->btn_add_wishlist->setStyleSheet(BTN_STYLE_DESIGN);

        ui->label_ic_add_wishlist->setPixmap(renderSvgToPixmap(ICON_SVG_ADD_WISH
                                                               ,btn_wishlist_size));
    }

    // btn_rm_order
    // label_ic_rm_order
    {
        QSize btn_rm_size = ui->btn_rm_order->size();
        btn_rm_size.setWidth(btn_rm_size.height()); // square

        ui->btn_rm_order->setStyleSheet(BTN_STYLE_DESIGN);

        ui->label_5->setPixmap(renderSvgToPixmap(ICON_SVG_RM_WISH
                                                               ,btn_rm_size));
        ui->label_5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }

    // btn_start_cf_ic
    // - btn_start_cf
    {
        QSize btn_start_size = ui->btn_start_cf->size();
        btn_start_size.setWidth(btn_start_size.height()); // square

        ui->btn_start_cf->setStyleSheet(BTN_STYLE_DESIGN);

        ui->btn_start_cf_ic->setPixmap(renderSvgToPixmap(ICON_SVG_START_CF
                                                               ,btn_start_size));
    }

    // groupbox
    ui->groupBox_select->setStyleSheet(GROUPBOX_OUTLINE_DESIGN);
    ui->groupBox_added->setStyleSheet(GROUPBOX_OUTLINE_DESIGN);

    // combox
    ui->combox_list_avail->clear();
    ui->combox_list_order->clear();


    // ==============================http client=================================
    // net work setup
    http_manager = new QNetworkAccessManager(this);

    // start check connection to dev board
    try_connect_to_dev_board();


    qDebug()<<this<<"- created window config logic layer";
}


// destructor
_b_config_logic_layer::~_b_config_logic_layer()
{
    delete ui;

    qDebug()<<this<<"- deleted window config logic layer";
}


// back to menu
void _b_config_logic_layer::on_btn_back_clicked()
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



// add to wishlist
void _b_config_logic_layer::on_btn_add_wishlist_clicked()
{
    int index = ui->combox_list_avail->currentIndex();

    if(index < 0 || index >= output_list.size())
    {
        ui->label_stat_select->setText("Invalid selection.");
        return;
    }

    lg_info_t selected_block = output_list[index];

    QString full_info = ui->label_stat_select->text(); // backup info board

    if(!check_board_available_before_add_block_to_wishlist())
    {
        // OK -> add to wish list
        wish_list.append(selected_block);
        ui->label_logic_if_log->setText(QString("%1\nAdded [%2] to wishlist")
                                            .arg(full_info,selected_block.lg_desc));
        ui->combox_list_order->addItem(selected_block.lg_desc);
    }
}



// commbox input list index changed
void _b_config_logic_layer::on_combox_list_avail_currentIndexChanged(int index)
{
    if (index < 0 || index >= output_list.size())
        return;

    const auto &block = output_list[index];

    QString info = QString("Board code: [%1]\nInfo: [%2]\n\nSelected logic block:\n- Code: %3\n- Desc: %4\n- Require: %5")
                       .arg(board_info.b_code,
                            board_info.b_desc,
                            block.lg_code,
                            block.lg_desc,
                            block.h_require);

    ui->label_stat_select->setText(info);
}


// commbix order list index changed
void _b_config_logic_layer::on_combox_list_order_currentIndexChanged(int index)
{
    if (index < 0 || index >= wish_list.size())
    {
        ui->label_logic_if_log->setText("No logic block selected.");
        return;
    }

    const auto &block = wish_list[index];

    QString info = QString("Logic block:\n- Code: %1\n- Desc: %2\n- Require: %3")
                       .arg(block.lg_code,
                            block.lg_desc,
                            block.h_require);

    ui->label_logic_if_log->setText(info);
}






// reconnect to devboard by default ip
void _b_config_logic_layer::try_connect_to_dev_board()
{
    // log
    // ui->label_stat_select->setText("Try connecting ...");
    // qDebug()<<"Try connecting ...";


    // create url to path get board type
    QString url = QString(HTTP_PATH_DEFAULT_DEV_BOARD_URL)
        + HTTP_PATH_GET_DEV_BOARD_TYPE;


    // create request
    QNetworkRequest request{QUrl(url)};
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      HTTP_MEDIA_TYPE_PLAIN_TEXT); // JSON

    // Create reply
    QNetworkReply *reply = nullptr;

    // GET request
    reply = http_manager->get(request);

    // emit after done
    // Note: in case page delete before emit we should
    //      + reply(this) <- set this is parent
    reply->setParent(this);

    connect(reply, &QNetworkReply::finished, this, [=]()
    {
        // delete reply after use
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            reconn_count++;
            ui->label_stat_select->setText(QString("Connect failed, Retry...[%1]").arg(this->reconn_count));

            QTimer::singleShot(2000,this,SLOT(try_connect_to_dev_board())); // retry each 2 second

            return;
        }

        // update board code
        this->board_info.b_code = reply->readAll();

        // update new data logic block code available for board to combox
        try_get_list_logic_block_available();
    });

}




/*
 * query then feedback in top input QStringList&
 * + clean if list not empty
 * + query table 'link_lcb_with_dev_board'
*/
void _b_config_logic_layer::try_get_list_logic_block_available()
{
    int ret = 0;

    // open database
    if(connectToSQLiteDB(DEV_BOARD_DESIGNED_DB_RSRC_PATH,DEV_BOARD_DESIGNED_DB_LOCAL_PATH,
            DEV_BOARD_DESIGNED_UNIQUE_CONNECT))
    {
        qDebug()<<this<< "Can't connect to database";
        ret = 1;
        qDebug()<<this<<"PAGE WILL DELETE WITH ERROR ["<< ret <<"]";

        this->deleteLater();
        return;
    }



    // get a query to table
    QSqlQuery query(QSqlDatabase::database(DEV_BOARD_DESIGNED_UNIQUE_CONNECT));




    // ====================================== Find board info


    // try find board inform
    query.prepare(QString(
        "SELECT * "
        "FROM \"%1\" "
        "WHERE [code_board] = :code")
                      .arg(DEV_BOARD_DESIGNED_TABLE_DEV_BOARD));

    query.bindValue(":code", this->board_info.b_code);

    if (!query.exec())
    {
        qDebug() << "Query error:" << query.lastError().text();

        // disconnect link to database
        disconnectFromSQLiteDB(DEV_BOARD_DESIGNED_UNIQUE_CONNECT);

        ret = 2;
        qDebug()<<this<<"PAGE WILL DELETE WITH ERROR ["<< ret <<"]";

        this->deleteLater();
        return;
    }
    else
    {
        if (query.next()) // go to query executed, false return if nothing
        {
            QString board_limit_hardware = query.value("hardware_limit").toString();

            // save board info
            this->board_info.b_desc = query.value("descript").toString();
            this->board_info.h_limit= board_limit_hardware;


            // parse JSON to get limit
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(board_limit_hardware.toUtf8(), &err);

            if (!err.error && doc.isObject())
            {
                QJsonObject rootObj = doc.object();
                QStringList limits_str_list;

                for (auto it = rootObj.begin(); it != rootObj.end(); it++) {
                    QString type = it.key();
                    QJsonObject range = it.value().toObject();

                    int s_id = range["s_id"].toInt();
                    int e_id = range["e_id"].toInt();
                    int capacity = e_id - s_id + 1;

                    limits_str_list.append(QString("%1: %2").arg(type, QString::number(capacity)));
                }

                QString full_info = QString("Board code: [%1]\nInfo: [%2]\nRemain:\n%3")
                                        .arg(this->board_info.b_code,
                                             this->board_info.b_desc,
                                             limits_str_list.join(", "));

                ui->label_stat_select->setText(full_info);
            }
            else
            {
                ui->label_stat_select->setText(QString("Board code: [%1]\nInfo: [%2]\nRemain: [JSON parse failed]")
                                                   .arg(this->board_info.b_code, this->board_info.b_desc));
            }
        }
        else // table type not found
        {
            ui->label_stat_select->setText(QString("Board code: [%1]\n"
                                                   "Info: No information found")
                                               .arg(this->board_info.b_code));
        }
    }


    // ====================================== Find logicblock available
    query.clear();

    query.prepare(QString(R"(
SELECT T3.code_logic, T3.hardware_require, T3.descript
FROM designed_dev_board AS T1
INNER JOIN link_lcb_with_dev_board AS T2
ON T1.code_board = T2.code_board
INNER JOIN logic_code_block AS T3
ON T2.code_logic = T3.code_logic
WHERE T1.code_board = :b_code
)"));

    query.bindValue(":b_code", this->board_info.b_code);

    if (!query.exec())
    {
        qDebug() << "Query error:" << query.lastError().text();

        // disconnect link to database
        disconnectFromSQLiteDB(DEV_BOARD_DESIGNED_UNIQUE_CONNECT);

        ret = 3;
        qDebug()<<this<<"PAGE WILL DELETE WITH ERROR ["<< ret <<"]";

        this->deleteLater();
        return;
    }

    else
    {
        // clean output list
        output_list.clear();
        qDebug()<<"Lg list clean before append";

        // add query to list
        while(query.next()) // go to query executed, false return if nothing
        {
            // append
            output_list.append({query.value("code_logic").toString(),
                                query.value("descript").toString(),
                                query.value("hardware_require").toString()});
        }

        // update to combox
        int ol_size = output_list.size();

        ui->combox_list_avail->clear();

        for (int i = 0; i < ol_size; i++)
        {
            // add to combox
            ui->combox_list_avail->addItem(output_list[i].lg_desc);
        }

    }

    // disconnect link to database
    disconnectFromSQLiteDB(DEV_BOARD_DESIGNED_UNIQUE_CONNECT);
}




/*
 * Check board available before add new logic block
 * - parse JSON of logic block requirement hardware
 * - parse JSON of dev board limit hardware
 * - handle:
 *  + foreach requirement in logicblock, find it exist in devboard
 *      + if not exist -> return -1, logic block unavailabe -> print require hardware name unvailable, print remain hardware
 *      + if exist requirement hardware then check enough slot:
 *          - check slot by child key "s_id" and "e_id" of limit hardware, and child key "n_order" of require hardware:
 *              + remain_slot = e_id - s_id + 1
 *              + check enough:
 *                  + if: remain_after = remain_slot - require <0 -> run out of slots
 *                      + print require hardware number order and [remain_hardware]
 *                  + else:
 *                      + update JSON limit of devboard by: s_id = s_id + require
 *                      + print success add to wishlist, print before, require, remain after
 */
int _b_config_logic_layer::check_board_available_before_add_block_to_wishlist()
{
    // Parse JSON from string
    QJsonParseError err;
    QJsonDocument dev_doc = QJsonDocument::fromJson(board_info.h_limit.toUtf8(), &err);
    if(err.error)
    {
        qDebug()<<"board document init fail";
        return -1;
    }

    QJsonDocument lg_doc = QJsonDocument::fromJson(output_list[ui->combox_list_avail->currentIndex()].h_require.toUtf8(), &err);
    if(err.error)
    {
        qDebug()<<"logic block document init fail";
        return -1;
    }

    QJsonObject dev_obj = dev_doc.object();
    QJsonObject lg_obj = lg_doc.object();

    // Browse all hardware logic block required
    for(auto it = lg_obj.begin(); it != lg_obj.end(); ++it) {
        QString type = it.key();

        if(!dev_obj.contains(type)) {
            qDebug() << "Board missing hardware: " << type;
            return -1;
        }

        int require = it.value().toObject().value("n_order").toInt();
        QJsonObject dev_hw = dev_obj[type].toObject();

        int s_id = dev_hw["s_id"].toInt();
        int e_id = dev_hw["e_id"].toInt();
        int remain = e_id - s_id + 1;

        if(remain < require) {
            qDebug() << "Not enough resourse: " << type << ", need: " << require << ", remain: " << remain;
            return -1;
        }

        // Else update
        dev_hw["s_id"] = s_id + require;
        dev_obj[type] = dev_hw;
    }

    // save new board_info.h_limit
    QJsonDocument new_dev_doc(dev_obj);
    board_info.h_limit = QString::fromUtf8(new_dev_doc.toJson(QJsonDocument::Compact));


    return 0;
}





void _b_config_logic_layer::on_btn_rm_order_clicked()
{
    int index = ui->combox_list_order->currentIndex();

    if(index < 0 || index >= wish_list.size()) {
        ui->label_logic_if_log->setText("Invalid selection to remove.");
        return;
    }

    lg_info_t removed_block = wish_list[index];

    // Parse current board info JSON
    QJsonParseError err;
    QJsonDocument dev_doc = QJsonDocument::fromJson(board_info.h_limit.toUtf8(), &err);
    QJsonDocument lg_doc = QJsonDocument::fromJson(removed_block.h_require.toUtf8(), &err);

    if (err.error || !dev_doc.isObject() || !lg_doc.isObject()) {
        ui->label_logic_if_log->setText("JSON parse error during removal.");
        return;
    }

    QJsonObject dev_obj = dev_doc.object();
    QJsonObject lg_obj = lg_doc.object();

    // Restore hardware slots by reverting requirement
    for (auto it = lg_obj.begin(); it != lg_obj.end(); ++it) {
        QString type = it.key();
        int released = it.value().toObject().value("n_order").toInt();

        if (dev_obj.contains(type)) {
            QJsonObject dev_hw = dev_obj[type].toObject();
            int s_id = dev_hw["s_id"].toInt();
            dev_hw["s_id"] = s_id - released;
            dev_obj[type] = dev_hw;
        }
    }

    // Update JSON string
    board_info.h_limit = QString::fromUtf8(QJsonDocument(dev_obj).toJson(QJsonDocument::Compact));

    // Remove from wishlist and update UI
    wish_list.removeAt(index);
    ui->combox_list_order->removeItem(index);

    ui->label_logic_if_log->setText(QString("Removed [%1] from order list.").arg(removed_block.lg_desc));
}






// update http file json to esp32
//#define HTTP_MEDIA_TYPE_JSON          "application/json"
//#define HTTP_MEDIA_TYPE_PLAIN_TEXT    "text/plain"
//#define HTTP_PATH_POST_FILE_CONFIG_LOGIC_BLOCK "/post_file_config_lgb"
/*
 * - Copy order list to another list, Re-arrange list by code name (sort)
 * - Copy board current inform
 * - have a check point  = NULL to check current logic block order code
 * - Create JSON config:
 *       + order logic block code, order id (because maybe repeat)
 *          + order id = 0
 *              + if order id != check point , order id ++
 *              + else keep order id
 *       + list hardware order recalculate by current hard ware limit
 *          + get board hardware current s_id -> hardware order e_id =  s_id - 1
 *          + success then  get hardware order s_id = e_id - hardware require
 *          + update board hardware current s_id -= hardware require
 *
 * - Hide this window
 * - New window open with param is : JSON config string
 *      + Window has a widget has ability display render image
 *          + render A form image (time, board infor, block info) can export in the future
 *          + user can re check the order config
 *      + Window has a button start send to board
 *          + http post "/post_file_config_lgb"
*/
void _b_config_logic_layer::on_btn_start_cf_clicked()
{
    // 0. Check empty
    if (this->wish_list.isEmpty()) {
        ui->label_log_cf_start->setText("Wishlist Empty");
        QTimer::singleShot(3000, this, [this]() {
            if (ui->label_log_cf_start->text() == "Wishlist Empty")
                ui->label_log_cf_start->setText("...");
        });
        return;
    }

    // 1. Sao chép và giữ trạng thái board ban đầu
    QList<lg_info_t> lg_sorted_list = this->wish_list;
    board_info_t board_info_origin = this->board_info;

    // 2. Sắp xếp logic block theo lg_code
    std::sort(lg_sorted_list.begin(), lg_sorted_list.end(),
              [](const lg_info_t& a, const lg_info_t& b)
              {
                  return a.lg_code < b.lg_code;
              });


    // 2.1. Parse board_info.h_limit
    QJsonParseError board_err;
    QJsonDocument board_doc = QJsonDocument::fromJson(board_info_origin.h_limit.toUtf8(), &board_err);
    if (board_err.error != QJsonParseError::NoError || !board_doc.isObject()) {
        ui->label_log_cf_start->setText("Parse error in board h_limit JSON");
        return;
    }

    QJsonObject board_obj = board_doc.object();



    // 3. Bắt đầu tạo cấu hình JSON
    QJsonArray json_a;
    int i = 0;
    while (i < lg_sorted_list.size()) {
        QString current_lg_code = lg_sorted_list[i].lg_code;

        // 3.1. Đếm số lần xuất hiện liên tiếp của logic block này
        int repeat_count = 0;
        while (i < lg_sorted_list.size() && lg_sorted_list[i].lg_code == current_lg_code) {
            ++repeat_count;
            ++i;
        }

        // 3.2. Lặp giảm dần từ repeat_count - 1 về 0
        for (int order_index = repeat_count - 1; order_index >= 0; --order_index) {
            QJsonObject json_lb;
            json_lb["lc"] = current_lg_code;
            json_lb["no"] = order_index;

            // 3.3. Parse yêu cầu phần cứng
            QJsonParseError lg_err;
            QJsonDocument req_doc = QJsonDocument::fromJson(lg_sorted_list[i+order_index-repeat_count].h_require.toUtf8(), &lg_err);
            if (lg_err.error != QJsonParseError::NoError || !req_doc.isObject()) {
                ui->label_log_cf_start->setText("Parse error in logic require JSON");
                return;
            }
            QJsonObject req_obj = req_doc.object();

            QJsonObject json_cf_obj;

            // 3.4. Xử lý từng loại phần cứng cần thiết
            for (auto it = req_obj.begin(); it != req_obj.end(); ++it) {
                QString hw_type = it.key();
                int needed = it.value().toObject().value("n_order").toInt();

                if (!board_obj.contains(hw_type))
                {
                    ui->label_log_cf_start->setText(QString("Missing hardware type: %1").arg(hw_type));
                    return;
                }

                QJsonObject hw_obj = board_obj[hw_type].toObject();
                int current_s_id = hw_obj["s_id"].toInt();  // đây là vị trí tiếp theo

                int level = repeat_count - 1 - order_index;
                int offset = level * needed;
                int e_id = current_s_id - 1 - offset;
                int s_id = e_id - needed + 1;

                if (s_id < 0) {
                    ui->label_log_cf_start->setText(QString("HW %1 out of resource").arg(hw_type));
                    return;
                }

                // Gán vào phần cấu hình của logic block này
                QJsonObject hw_range;
                hw_range["s_id"] = s_id;
                hw_range["e_id"] = e_id;
                json_cf_obj[hw_type] = hw_range;

                // Nếu đang ở order_index == 0 (cuối cùng của block này), cập nhật board
                if (order_index == 0) {
                    hw_obj["s_id"] = s_id;
                    board_obj[hw_type] = hw_obj;
                }
            }

            json_lb["cf"] = json_cf_obj;
            json_a.append(json_lb);
        }


        // 3.5. Go to next logic block group
    }

    // 3.6. Sau khi xử lý xong, cập nhật lại board_info_origin.h_limit
    QJsonDocument updated_board_doc(board_obj);
    board_info_origin.h_limit = QString::fromUtf8(updated_board_doc.toJson(QJsonDocument::Compact));



    // 4. Kết thúc, tạo document JSON cuối cùng
    QJsonDocument final_doc(json_a);
    QString final_json_str = final_doc.toJson(QJsonDocument::Compact);
    qDebug() << "Generated config JSON:\n" << final_json_str;

    ui->label_log_cf_start->setText("Created configuration OK!");


    // Hide this window
    // create new preview and input :
    //  + this pointer
    //  + struct board_info_origin
    //  + JSON config minimum requirements for esp32

    _b__preview_and_config* preview_page = new _b__preview_and_config(
        board_info_origin,final_json_str, this);// << no set parent because when current window hide
                            // preview page will hide

    // connect signal auto re show this page when close preview page
    QObject::connect(preview_page, SIGNAL(preview_page_closed()),
                     this, SLOT(try_show_this_page_if_hide()));

    // hide this
    this->hide();
    preview_page->show();
}


// try show this window after preview page close
void _b_config_logic_layer::try_show_this_page_if_hide()
{
    // show
    this->show();
}
