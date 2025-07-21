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
 *  - ledit_url_broker
 *  - ledit_port_broker
 *  - ledit_username
 *  - ledit_password
 *
 *  - label_log_status
 *
 *  - label_ic_reconn
 *  - btn_reconn
 *
 *  - tabwid_logic_controller
 *
========================================================================== */


/* ==========================================================================
 * Description
 * - Function:
 *      + Query to database 'app_net_service' -> 'mqtt_client_inform' table
 *          + update old inform: URL, PORT, Username
 *          + Password did not save in datebase
 *
 *      + Login to broker
 *          + If success:
 *              + get content of these topic:
 *                  ~ maintain_flag,
 *                  ~ board_config
 *                  => all of these flag check sequence form high to low, if timeout -> server on maintain
 *                  => otherwise:
 *                      + parse board_config: logic_block_code/order_number
 *                      + query in table 'dev_board_designed' -> 'logic_code_block' table
 *                          + create UI controller
 *
 *      + Send / get topic by UI controller
 *          + logic ui
========================================================================== */




/* ==========================================================================
 * Definition
========================================================================== */
#include "_a_login_to_broker.h"
#include "ui__a_login_to_broker.h"


// QString host_url = "7b92f852aa7b4f20a563529b35a8bd79.s1.eu.hivemq.cloud";
// QString user_name = "mqtt_qt";
// QString pass_word = "A123456_abc";
// int port_num = 8883;

// icon
#define ICON_SVG_BACK ":/icon/rsrc/Icon/feather/arrow-left.svg"
#define ICON_SVG_RECONN ":/icon/rsrc/Icon/feather/download-cloud.svg"

// mqtt/ sql

#define MQTT_DEFAULT_ORDER_DATA_ID  0 // Not new login data
#define MQTT_LAST_ORDER_DATA_ID     1 // Old login data (no password)


#define MQTT_DEFAULT_PROTOCOL_VERSION QMqttClient::MQTT_3_1_1




/* ==========================================================================
 * Class
========================================================================== */

// instruction
// create ui
// design ui
// config default ui inform
// create mqtt_client
_a_login_to_broker::_a_login_to_broker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::_a_login_to_broker)
{
    uint8_t ret =0;

    ui->setupUi(this);
    this->setWindowTitle("Login to broker");


    //==========================Style ================

    // set frame functions list ( see example combinations F1)
    ui->frame_login_broker->setFrameShape(QFrame::Box);
    ui->frame_login_broker->setFrameShadow(QFrame::Sunken);
    ui->frame_login_broker->setLineWidth(1);//ptx
    ui->frame_login_broker->setMidLineWidth(3);



    // button and label

    // set button/ label back
    QSize btn_back_size = ui->btn_back->size();
    btn_back_size.setWidth(btn_back_size.height()); // square

    ui->btn_back->setStyleSheet(BTN_STYLE_DESIGN);

    ui->label_ic_back->setPixmap(renderSvgToPixmap(ICON_SVG_BACK
                                                   ,btn_back_size));



    // label_ic_reconn
    // btn_reconn
    QSize btn_reconn_size = ui->btn_reconn->size();
    btn_reconn_size.setWidth(btn_reconn_size.height()); // square

    ui->btn_reconn->setStyleSheet(BTN_STYLE_DESIGN);

    ui->label_ic_reconn->setPixmap(renderSvgToPixmap(ICON_SVG_RECONN
                                                   ,btn_reconn_size));



    // clean tab widget, set tab default West (<-)
    // clear_UI_tabWidget();
    ui->tabWidget_UI_controller->setTabPosition(QTabWidget::West);


    for(int i = 0; i<10; i++)
    {
    ui->tabWidget_UI_controller->addTab(new QWidget(), "new tab");
    }

    ui->tabWidget_UI_controller->setStyleSheet(TAB_SCROLL_BUTTON_STYLE);


    //========================== Limit input ================

    // input port
    // Note: QIntValidator is QObject (no copy, must have parent)
    ui->ledit_port_broker->setValidator(new QIntValidator(0, 65535,ui->ledit_port_broker));






    //==========================Inform Config ================

    // connect, get mqtt default data
    if(connectToSQLiteDB(NET_SERVICE_INFORM_DB_RSRC_PATH, NET_SERVICE_INFORM_DB_LOCAL_PATH, NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE))
    {
        qDebug()<<this<< "Can't connect to database";

        ret = 1;
        qDebug()<<this<<"PAGE WILL DELETE WITH ERROR ["<< ret <<"]";

        this->deleteLater();
        return;
    }




    // get mqtt default data
    QSqlQuery query(QSqlDatabase::database(NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE));


    // try find lastest user input inform
    query.prepare(QString("SELECT * FROM ") + MQTT_CLIENT_INFORM_TABLE + " WHERE order_id="+ QString::number(MQTT_LAST_ORDER_DATA_ID));

    if (!query.exec())
    {
        qDebug() << "Query error:" << query.lastError().text();

        // unconnect link to database
        disconnectFromSQLiteDB(NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE);

        ret = 2;
        qDebug()<<this<<"PAGE WILL DELETE WITH ERROR ["<< ret <<"]";

        this->deleteLater();
        return;
    }

    if (query.next()) // go to query executed, false return if nothing
    {
        //  lastest user input inform is found
        qDebug() << "Using LAST login data";


        // write new data to line edit
        ui->ledit_url_broker->setText(
            query.value("broker_url").toString());

        ui->ledit_port_broker->setText(
            query.value("broker_port").toString());

        ui->ledit_username->setText(
            query.value("username").toString());

    }
    else
    {
        // lastest user input inform not exist
        // try use default

        query.prepare(QString("SELECT * FROM ") + MQTT_CLIENT_INFORM_TABLE + " WHERE order_id="+ QString::number(MQTT_DEFAULT_ORDER_DATA_ID));

        if (!query.exec()) {
            qDebug() << "Fallback query error:" << query.lastError().text();

            // unconnect link to database
            disconnectFromSQLiteDB(NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE);

            ret = 3;
            qDebug()<<this<<"PAGE WILL DELETE WITH ERROR ["<< ret <<"]";

            this->deleteLater();
            return;
        }

        if (query.next()) {
            // Callback default (id = 0)
            qDebug() << "Using DEFAULT login data";

            // write data to widget
            ui->ledit_url_broker->setText(
                query.value("broker_url").toString());

            ui->ledit_port_broker->setText(
                query.value("broker_port").toString());

            ui->ledit_username->setText(
                query.value("username").toString());
        }
        else
        {
            // missing all
            qDebug() << "No login data found at all.";

            ui->ledit_url_broker->setText(
                query.value("mqtts://yourbroker.url").toString());

            ui->ledit_port_broker->setText(
                query.value("8883").toString());

            ui->ledit_username->setText(
                query.value("your username").toString());
        }
    }


    // disconnect link to database
    disconnectFromSQLiteDB(NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE);







    // ========================================= MQTT service
    // init client
    this->mqtt_client = new(std::nothrow) QMqttClient(this); // << because it is QObject , auto free when 'this' parent free

    if(!(this->mqtt_client))
    {
        ret = 4;
        qDebug()<<this<<"- mqtt client alloc failed ["<<ret<<"]";
        return;
    }

    qDebug()<<this<<"- mqtt client created";


    // connect signal mqtt with slot handle
    connect(this->mqtt_client, &QMqttClient::connected, this, &_a_login_to_broker::on_mqtt_connected);
    connect(this->mqtt_client, &QMqttClient::disconnected, this, &_a_login_to_broker::on_mqtt_disconnected);

    connect(this->mqtt_client, &QMqttClient::messageReceived, this, &_a_login_to_broker::on_mqtt_messageReceived);
    connect(this->mqtt_client, &QMqttClient::messageSent, this, &_a_login_to_broker::on_mqtt_messageSent);




    // =========================================================== ok
    qDebug()<<this<<"- created window login";

}



// destruction
_a_login_to_broker::~_a_login_to_broker()
{
    delete ui;

    qDebug()<<this<<"- deleted window login";
}





// back to menu
void _a_login_to_broker::on_btn_back_clicked()
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




/*
 *  submit all line edit have broker information to broker
 *  - set  'ledit_log_status'  -> Reconnecting ...
 *  - start mqtt connect
 */
void _a_login_to_broker::on_btn_reconn_clicked()
{
    // ===============================================Check input

    // status change reconnect
    ui->label_log_status->setText("Checking ...");
    // check input
    QString broker_url = ui->ledit_url_broker->text();
    uint16_t broker_port = ui->ledit_port_broker->text().toInt();
    QString username = ui->ledit_username->text();
    QString password = ui->ledit_password->text();


    // check if connecting
    if (mqtt_client->state() == QMqttClient::Connected ||
        mqtt_client->state() == QMqttClient::Connecting)
    {
        ui->label_log_status->setText("Try reconnect ...");
        mqtt_client->disconnectFromHost();
    }


    // =========================================== config mqtt client
    // edit HiveMQ cluster
    mqtt_client->setHostname(broker_url);
    mqtt_client->setPort(broker_port);
    mqtt_client->setUsername(username);
    mqtt_client->setPassword(password);


    // TLS
    mqtt_client->setProtocolVersion(MQTT_DEFAULT_PROTOCOL_VERSION);


    // connect

    // config ssl (Secure Sockets Layer)/tls (Transport Layer Security)
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();

    // connect to host
    this->mqtt_client->connectToHostEncrypted(sslConf);

}








/* ===================================================
 * MQTT SLOT HANDLE
 * ===================================================
 */


/* connected
 *  - update new ui implement
 *      - check maintain flag is set or not set
 *
*/
void _a_login_to_broker::on_mqtt_connected()
{
    //=========================================== UPDATE CONNECTION

    // save new data to database
    ui->label_log_status->setText("Connected to broker\nSaving information");

    // save new data to database
    if(connectToSQLiteDB(NET_SERVICE_INFORM_DB_RSRC_PATH,
                          NET_SERVICE_INFORM_DB_LOCAL_PATH,
                          NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE))
    {
        qDebug().noquote()<< "mqtt save information fail\nPrepare delete page!!!";
        this->deleteLater();
        return;
    }
    else // try update to table
    {
        QSqlQuery update_query(QSqlDatabase::database(NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE));

        // update new connection in lastest inform
        update_query.prepare(QString("UPDATE %1 SET broker_url = :url, "
                              "broker_port = :port, "
                              "username = :username "
                              "WHERE order_id = :id")
                                .arg(MQTT_CLIENT_INFORM_TABLE));
        update_query.bindValue(":url", ui->ledit_url_broker->text());
        update_query.bindValue(":port", ui->ledit_port_broker->text().toInt());
        update_query.bindValue(":username", ui->ledit_username->text());
        update_query.bindValue(":id", MQTT_LAST_ORDER_DATA_ID);

        if (!update_query.exec() || !(update_query.numRowsAffected()))
        {
            // Note:
            //  update query return true if not find matching
            //  -> solution check update_query.numRowsAffected() >0

            qDebug().noquote() << "Update fail, try insert...\n=>"
                                << update_query.lastError().text();


            // try insert new
            QSqlQuery insert_Query(QSqlDatabase::database(NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE));
            insert_Query.prepare(QString("INSERT INTO %1 (order_id, broker_url, broker_port, username) "
                                        "VALUES (:id, :url, :port, :username)")
                                    .arg(MQTT_CLIENT_INFORM_TABLE));

            insert_Query.bindValue(":id", MQTT_LAST_ORDER_DATA_ID);
            insert_Query.bindValue(":url", ui->ledit_url_broker->text());
            insert_Query.bindValue(":port", ui->ledit_port_broker->text().toInt());
            insert_Query.bindValue(":username", ui->ledit_username->text());

            if (!insert_Query.exec())
            {
                qDebug().noquote() << "Try insert fail!\n=>" << insert_Query.lastError().text()
                    << "\nPrepare delete page!";
                this->deleteLater();
                return;
            }
            else
            {
                qDebug() << "Insert successfull";
            }
        }
        else
        {
            qDebug() << "Updated successful";
        }
    }

    // ok then disconnect to db
    disconnectFromSQLiteDB(NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE);



    //=========================================== CHECK SERVER STATUS
    // check maintain flag
    ui->label_log_status->setText("Checking connection status ...");

    // try subcribe to maintain flag topic
    // try subcribe to board config topic
    QMqttTopicFilter maintain_flag_topic(MQTT_GENERAL_HANDSHAKE_TOPIC_MAINTAIN_FLAG);
    QMqttTopicFilter board_config_topic(MQTT_GENERAL_HANDSHAKE_TOPIC_DEV_BOARD_CONFIG_INFO);

    this->mqtt_client->subscribe(maintain_flag_topic, MQTT_GENERAL_HANDSHAKE_SUBCRIBE_DEFAULT_MAX_QOS);
    this->mqtt_client->subscribe(board_config_topic, MQTT_GENERAL_HANDSHAKE_SUBCRIBE_DEFAULT_MAX_QOS);

    // subcribe return QMqttSubcription to follow connect (comming soon)
}



/* mqtt disconnected
 * - Clear all tabwidget (delete them else memory leak)
*/
void _a_login_to_broker::on_mqtt_disconnected()
{
    // check maintain flag
    ui->label_log_status->setText("Disconnected  !!!");

    // clear ui controller block
    clear_UI_tabWidget();

    qDebug()<< "All UI_controller are deleted !";
}






/* A new message received
 * - Logic check:
 *      + (1) handshake message:
 *          ~ maintain flag: (see __general_handshake_topic.h)
 *              + if 0 (good)-> Esp32 is configured and ready to be controlled
 *                             -> sometime is esp32 turn off, control send topic
 *                                  should have a feedback topic
 *              + if 1 (busy)-> Esp32 is updating
 *
 *      + (2) receive config devboard from [MQTT_GENERAL_HANDSHAKE_TOPIC_DEV_BOARD_CONFIG_INFO]
 *          + message to user know new refresh tabWidget
 *          + clean and delete all tab of tabWidget
 *          + parse config -> call back function implement QWidget
 *          + CONFIG format: [logic block code]/[index]/[logic block code]/[index]...\0
 *
*/
void _a_login_to_broker::on_mqtt_messageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    QString recev_message = QString::fromUtf8(message); // convert  utf8 -> utf16 (QString)
    QString topic_name = topic.name();




    // (1) handshake message ========================================================
    // switch (topic): << no switch can't understand QString


    // check maintain flag
    if(topic_name == MQTT_GENERAL_HANDSHAKE_TOPIC_MAINTAIN_FLAG)
    {
        // server under maintain or good to comunicate
        if( (int)recev_message.toInt() != (int)(MQTT_GENERAL_HANDSHAKE_MAINTAIN_FLAG_GOOD))
            // :) compare with good(0) better than check busy(1) because it maybe !1 if something wrong
        {
            ui->label_log_status->setText("Server is under maintenance !!!");
        }
        else
        {
            ui->label_log_status->setText("Ready to initialize interface...");
        }
    }




    // check if configuration string is received
    // clean tabWidget
    // parse it and send topic to create Widget
    else if(topic_name == MQTT_GENERAL_HANDSHAKE_TOPIC_DEV_BOARD_CONFIG_INFO)
    {
        // clean
        clear_UI_tabWidget();


        // parse CONFIG format: [logic block code]/[index]/[logic block code]/[index]...\0
        QStringList tokens = recev_message.split('/');

        if (tokens.size() % 2 != 0) {
            qDebug() << "Token not %2 = 0 !";
            return;
        }

        // ask helper "_a_ltb_000_logic_base_map.h"
        for(int i = 0; i< tokens.size();i+=2)
        {
            // pointer new Widget
            QWidget* new_tab = nullptr;


            // ask helper get a Widget
            if(!Check_logic_block_code_then_init_widget(& new_tab, tokens[i] , tokens[i+1] ,this->mqtt_client))
            { // return 0 is ok
                ui->tabWidget_UI_controller->addTab(new_tab, tokens[i]+"_"+tokens[i+1]);
            }
            else // missing logic block match with code received
            {
                qDebug() << "Missing logic block UI code ["<<tokens[i]<<"] idx ["<<tokens[i+1]<<"]";
            }
        }
    }

    // else donothing, ignore it
}






/* message sent success (this use to display topic topic has reached broker)
 * + message ID sent to broker
 * + when interract with UI logic block, if see feedback message ID change -> send success
 * */
void _a_login_to_broker::on_mqtt_messageSent(qint32 id)
{
    // Note: never get sent message ACK if we use default QOS 0
    // in file "__general_handshake_topic.h" i config send is QOS 1
    ui->label_log_status->setText(QString("SENT ID [%1]").arg(id));

    qDebug()<<QString("sent mes []").arg(id);
}




// Support clean UI tabwidget
void _a_login_to_broker::clear_UI_tabWidget()
{
    // ui->tabWidget_UI_controller->clear(); // <<< Danger leak memory only
    for (int i = ui->tabWidget_UI_controller->count() - 1; i >= 0; --i)
    {
        QWidget* tab =  ui->tabWidget_UI_controller->widget(i); // get pointer to tab

        ui->tabWidget_UI_controller->removeTab(i); // Note: tabwidget only remove not delete tab
            // it is convenient for reuse in future

        delete tab;  // here i delete this tab with it child
    }

}
