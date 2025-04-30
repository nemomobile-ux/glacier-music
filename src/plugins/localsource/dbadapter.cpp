/*
 * Copyright (C) 2021-2025 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "dbadapter.h"

#include <QDebug>
#include <QDir>
#include <QSqlQueryModel>
#include <QtSql>

static dbAdapter* dbAdapterInstance = 0;

dbAdapter::dbAdapter(QObject* parent)
    : QObject(parent)
    , m_isValid(false)
{
    QMutexLocker locker(&lock);
    m_db = _getDatabase();
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

void dbAdapter::initDB(QSqlDatabase db)
{
    if (!db.open()) {
        qFatal() << db.lastError().text();
    }
    db.exec("CREATE TABLE `artist` (`id` INTEGER PRIMARY KEY AUTOINCREMENT,`name` TEXT )");
    db.exec("INSERT INTO `artist` (`id`, `name`) VALUES ('0','Unknown Artist')");
    db.exec("CREATE TABLE `tracks` (`id` INTEGER PRIMARY KEY AUTOINCREMENT, \
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
    db.exec("CREATE TABLE `playlist` (`id`	INTEGER PRIMARY KEY AUTOINCREMENT, \
            `song_id`	INTEGER NOT NULL, \
            `time`	INTEGER NOT NULL)");
    db.exec("CREATE UNIQUE INDEX artist_idx ON artist(name)");
    db.exec("CREATE UNIQUE INDEX song_idx ON songs(artist_id,title,album,track,year)");
    db.exec("CREATE UNIQUE INDEX plst_idx ON playlist(song_id,time)");
    emit baseCreate();
}

QSqlDatabase dbAdapter::_getDatabase()
{
    // Starting with Qt 5.11, sharing the same connection between threads is not allowed.
    // We use a dedicated connection for each thread requiring access to the database,
    // using the thread address as connection name.
    const QString threadAddress = QLatin1String("0x") + QString::number((quintptr)QThread::currentThreadId(), 16);

    QSqlDatabase db = QSqlDatabase::database(threadAddress);
    if (db.isOpen() && db.isValid()) {
        return db;
    } else {
        qDebug() << "Creating new database connection for thread";
        db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"), threadAddress);
    }
    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/db.sql");

    if (!db.open()) {
        qDebug() << db.lastError().text();
    }

    qDebug() << "Load DB from " << QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/db.sql";

    if (QFile(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/db.sql").size() == 0) {
        qDebug() << "Init db";
        initDB(db);
    }

    if (!db.isValid()) {
        qFatal("Can't load DB");
    }

    if (!m_isValid) {
        m_isValid = true;
        emit isValidChanged();
    }
    return db;
}

bool dbAdapter::isValid() const
{
    return m_isValid;
}
