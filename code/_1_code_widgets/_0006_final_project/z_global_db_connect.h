#ifndef Z_GLOBAL_DB_CONNECT_H
#define Z_GLOBAL_DB_CONNECT_H


/* =======================================================
 * Definition
======================================================= */

// c
#include <stdint.h>

// SQLite
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQuery>

// FILE sys
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>


// Copy db to local
/* Note 2: UPDATE Database
 *  + problem use database, qresouce can't use like system folder
 *      database need copy into default application path permiss of OS
 *         + Solution: define a macro APPVERSION keep complile time
 *         + check compile time then compare with database modified time
 *         + delete old database then create new if new update
 *  + problem: database can modify in runtime -> wrong update version
 *         + solution: create unique empty file "/version"
 *         + check modified this file
 *              + if new update -> touch file to update modify
*/
#include <QStandardPaths> // available read write folder default OS create for this app

// clean db each time update
#define APP_VERSION __DATE__ " " __TIME__

#define APP_VERSION_SAVE_FILE_PATH   "/verison.old"



// ============================================================== db infor

// net service db
#define NET_SERVICE_INFORM_DB_LOCAL_PATH "/app_net_service.db"
#define NET_SERVICE_INFORM_DB_RSRC_PATH  ":/database/rsrc/Database/app_net_service.db" //database

#define MQTT_CLIENT_INFORM_TABLE     "mqtt_client_inform" //table mqtt client info


// connect database of page a login to broker
#define NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE "a_login_connect_nsi_db"




// board designed db
#define DEV_BOARD_DESIGNED_DB_LOCAL_PATH "/dev_board_designed.db"
#define DEV_BOARD_DESIGNED_DB_RSRC_PATH  ":/database/rsrc/Database/dev_board_designed.db" //database

#define DEV_BOARD_DESIGNED_TABLE_DEV_BOARD      "designed_dev_board" //table mqtt client info
#define DEV_BOARD_DESIGNED_TABLE_LOGIC_BLOCK    "logic_code_block"
#define DEV_BOARD_DESIGNED_TABLE_LINK_DB_LB     "link_lcb_with_dev_board"

#define DEV_BOARD_DESIGNED_UNIQUE_CONNECT "connect_devboard_designed_db"


// connect database of page a login to broker
#define NET_SERVICE_INFORM_UNIQUE_CONNECT_A_LOGIN_PAGE "a_login_connect_nsi_db"




/* =======================================================
 * API
======================================================= */
// connect to db
uint8_t connectToSQLiteDB(const QString& db_rsrc_path, const QString& db_local_path,const QString& unique_connect );

// disconnect
void disconnectFromSQLiteDB(const QString &unique_connect);


#endif // Z_GLOBAL_DB_CONNECT_H
