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
    db.exec("CREATE TABLE `artist` (`id` INTEGER PRIMARY KEY AUTOINCREMENT,`name` TEXT )");
    db.exec("CREATE TABLE `tracks` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, \
            `artist_id` INTEGER NOT NULL, \
            `filename` TEXT NOT NULL,\
            `title` TEXT NOT NULL,\
            `album` TEXT,\
            `comment` TEXT,\
            `genre` TEXT, \
            `track` INTEGER,\
            `year` INTEGER,\
            `length` INTEGER)");
    db.exec("CREATE TABLE `playlist` (`id`	INTEGER PRIMARY KEY AUTOINCREMENT, \
            `song_id`	INTEGER NOT NULL, \
            `time`	INTEGER NOT NULL)");
    db.exec("CREATE UNIQUE INDEX artist_idx ON artist(name)");
    db.exec("CREATE UNIQUE INDEX song_idx ON songs(artist_id,title,album,track,year)");
    emit baseCreate();
}
