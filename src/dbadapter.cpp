#include "dbadapter.h"

#include <QtSql>
#include <QSqlQueryModel>
#include <QDir>

static dbAdapter *dbAdapterInstance = 0;

dbAdapter::dbAdapter(QObject *parent) : QObject(parent)
{
    QMutexLocker locker(&lock);
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/db.sql");

    if(!db.open())
    {
        qDebug() << db.lastError().text();
    }



    if(QFile(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/db.sql").size() == 0)
    {
        initDB();
    }
}

dbAdapter::~dbAdapter()
{
    db.close();
}

dbAdapter& dbAdapter::instance(){
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if(!dbAdapterInstance) dbAdapterInstance = new dbAdapter();
    return *dbAdapterInstance;
}

void dbAdapter::initDB()
{
    db.exec("CREATE TABLE `files` ( \
            `id`	INTEGER PRIMARY KEY AUTOINCREMENT, \
            `path`	TEXT, \
            `artist`	TEXT DEFAULT 'Unknow artist', \
            `track`	TEXT DEFAULT 'Unknow track', \
            `rate`	INTEGER DEFAULT 100, \
            `lastplay`	INTEGER, \
            `updated`	INTEGER DEFAULT 0 );");

    emit baseCreate();
}
