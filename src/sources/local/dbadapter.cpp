#include "dbadapter.h"

#include <QDebug>
#include <QDir>
#include <QSqlQueryModel>
#include <QtSql>

static dbAdapter* dbAdapterInstance = 0;

dbAdapter::dbAdapter(QObject* parent)
    : QObject(parent)
{
    QMutexLocker locker(&lock);
    m_db = getDatabase();
}

dbAdapter::~dbAdapter()
{
    m_db.close();
}

dbAdapter& dbAdapter::instance()
{
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if (!dbAdapterInstance) {
        dbAdapterInstance = new dbAdapter();
    }
    return *dbAdapterInstance;
}

void dbAdapter::initDB()
{
    m_db.exec("CREATE TABLE `artist` (`id` INTEGER PRIMARY KEY AUTOINCREMENT,`name` TEXT )");
    m_db.exec("INSERT INTO `artist` (`id`, `name`) VALUES ('0','Unknown Artist')");
    m_db.exec("CREATE TABLE `tracks` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, \
            `artist_id` INTEGER NOT NULL, \
            `filename` TEXT NOT NULL,\
            `title` TEXT NOT NULL,\
            `album` TEXT,\
            `comment` TEXT,\
            `genre` TEXT, \
            `cover` TEXT, \
            `track` INTEGER,\
            `year` INTEGER,\
            `length` INTEGER)");
    m_db.exec("CREATE TABLE `playlist` (`id`	INTEGER PRIMARY KEY AUTOINCREMENT, \
            `song_id`	INTEGER NOT NULL, \
            `time`	INTEGER NOT NULL)");
    m_db.exec("CREATE UNIQUE INDEX artist_idx ON artist(name)");
    m_db.exec("CREATE UNIQUE INDEX song_idx ON songs(artist_id,title,album,track,year)");
    m_db.exec("CREATE UNIQUE INDEX plst_idx ON playlist(song_id,time)");
    emit baseCreate();
}

QSqlDatabase dbAdapter::getDatabase()
{
    // Starting with Qt 5.11, sharing the same connection between threads is not allowed.
    // We use a dedicated connection for each thread requiring access to the database,
    // using the thread address as connection name.
    const QString threadAddress = QLatin1String("0x") + QString::number((quintptr)QThread::currentThreadId(), 16);

    QSqlDatabase db = QSqlDatabase::database(threadAddress);
    if (db.isOpen() && db.isValid()) {
        return db;
    } else {
        qDebug() << "Creating new database connection for thread" << threadAddress;
        db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), threadAddress);
    }
    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/db.sql");

    if (!db.open()) {
        qDebug() << db.lastError().text();
    }

    qDebug() << "Load DB from " << QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/db.sql";

    if (QFile(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/db.sql").size() == 0) {
        qDebug() << "Init db";
        initDB();
    }

    if (!db.isValid()) {
        qFatal("Can't load DB");
    }

    return db;
}
