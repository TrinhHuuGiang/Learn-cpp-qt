/* =======================================================
 * Definition
======================================================= */

#include "z_global_db_connect.h"




/* ======================================================
 * Prototype
=========================================================*/
static QDateTime getAppBuildDateTime();

static bool renew_local_db_when_version_update(const QString& db_rsrc_path, const QString& db_local_path);


/* =======================================================
 * APIs Code
======================================================= */


// connect to db
uint8_t connectToSQLiteDB(const QString& db_rsrc_path, const QString& db_local_path,const QString& unique_connect )
{
    // check update
    if(!renew_local_db_when_version_update(db_rsrc_path, db_local_path))
    {
        qDebug() << "check version db failed";
        return 1;
    }

    // get default OS read/write able path
    QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // sqlite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", unique_connect);

    // database
    db.setDatabaseName(appDataDir + db_local_path);

    if (!db.open()) {
        qDebug() << "Can't open database:" << db.lastError().text();
        return 2;
    }

    // success
    qDebug() << "Connected database: ["<< appDataDir + db_local_path << "]";
    return 0;
}



// disconnect db
void disconnectFromSQLiteDB(const QString &unique_connect)
{
    // check connect to db
    if (!QSqlDatabase::contains(unique_connect))
    {
        qDebug() << "No such connection to disconnect: [" << unique_connect << "]";
        return;
    }

    // close db
    {// << if not block these code a log warning:
                        // QSqlDatabasePrivate::removeDatabase: connection 'a_login_connect_nsi_db' is still in use, all queries will cease to work.

        QSqlDatabase db = QSqlDatabase::database(unique_connect, false);
        if (db.isOpen()) {
            db.close();
        }
    }

    // disconnect from manage system
    QSqlDatabase::removeDatabase(unique_connect);

    qDebug() << "Disconnected database: [" << unique_connect << "]";
}




/* =======================================================
 * Support code
======================================================= */
static QDateTime getAppBuildDateTime() {
    QString dateStr = APP_VERSION;
    dateStr = dateStr.simplified();
    // :) __DATE__ and __TIME__ return a string but have " " at start and end
    // and QDateTime can't parse this format -> simplified
    return QDateTime::fromString(dateStr, "MMM d yyyy HH:mm:ss");
}


static bool renew_local_db_when_version_update(const QString& db_rsrc_path, const QString& db_local_path)
{
    // get default OS read/write able path
    QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataDir); // make folder if not exist

    QString fullDbPath = appDataDir + db_local_path;
    QString versionFilePath = appDataDir + APP_VERSION_SAVE_FILE_PATH;


    // check file database info
    QFileInfo dbInfo(fullDbPath);
    QFileInfo versionFileInfo(versionFilePath);


    // if database not exist , try copy from qresource
    // if file version not exist,  try copy from qresource <= maybe first time install app
    if (!dbInfo.exists() || !versionFileInfo.exists())
    {
        qDebug() << "[DB] First install or version flag missing. Copying DB...";
        if (QFile::copy(db_rsrc_path, fullDbPath))
        {
            QFile::setPermissions(fullDbPath, QFileDevice::ReadOwner | QFileDevice::WriteOwner);
            // if missing WriteOwner
            // + we can't remove file database inthe future when new update
            // + we can't update data to database inthe future

            QFile flag(versionFilePath);
            flag.open(QIODevice::WriteOnly | QIODevice::Truncate);
            flag.close();

            qDebug() << "[DB] Created version flag.";
            return true;
        }
        else
        {
            qDebug() << "[DB] Failed to copy database.";
            return false;
        }
    }


    // if exist file version, check version
    QDateTime appBuildTime = getAppBuildDateTime();
    QDateTime dbLastModified = versionFileInfo.lastModified();


    // check new update
    qDebug() << "[DB] App build time:" << appBuildTime.toString();
    qDebug() << "[DB] Old version:" << dbLastModified.toString();

    // if new version -> delete database then renew one
    if (appBuildTime > dbLastModified)
    {
        qDebug() << "[DB] App is newer than DB. Updating...";

        // before remove
        if (!QFile(fullDbPath).remove())
        {
            QFile f_db(fullDbPath);
            qDebug() << "Permissions:" << f_db.permissions();
            qDebug() << "[DB] Failed to remove old database ["<<fullDbPath<<"]";
            return false;
        }

        if( QFile::copy(db_rsrc_path, fullDbPath))
        {
            // set permission
            QFile::setPermissions(fullDbPath, QFileDevice::ReadOwner | QFileDevice::WriteOwner);

            // touch to file version :) to save laster modify
            QFile f_update (versionFilePath);
            if (f_update.open(QIODevice::WriteOnly))
            {
                f_update.close();
                return true;
            }
            else
            {
                qDebug() << "[DB] Failed to update version flag";
                return false;
            }
        }
        else
        {
            qDebug() << "[DB] Failed to copy new database.";
            return false;
        }
    }

    qDebug() << "[DB] Database is newest. Nothing update";
    return true; // nothing update
}

