/*
 * Copyright (C) 2021-2022 Chupligin Sergey <neochapay@gmail.com>
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

#include "playlistmodel.h"

#include <track.h>
#include <dbadapter.h>

#include <QSqlDatabase>
#include <QSqlQuery>

PlayListModel::PlayListModel(QObject *parent) :
    QAbstractListModel(parent)
  , m_playMode(PlayMode::Random)
  , m_repeatMode(RepeatMode::NoneRepeat)
{
    hash.insert(Qt::UserRole ,QByteArray("trackId"));
    hash.insert(Qt::UserRole+1 ,QByteArray("artist"));
    hash.insert(Qt::UserRole+2 ,QByteArray("artist_id"));
    hash.insert(Qt::UserRole+3 ,QByteArray("title"));
    hash.insert(Qt::UserRole+4 ,QByteArray("fileName"));
    hash.insert(Qt::UserRole+5 ,QByteArray("cover"));
    hash.insert(Qt::UserRole+6 ,QByteArray("album"));
    hash.insert(Qt::UserRole+7 ,QByteArray("comment"));
    hash.insert(Qt::UserRole+8 ,QByteArray("genre"));
    hash.insert(Qt::UserRole+9 ,QByteArray("year"));
    hash.insert(Qt::UserRole+10 ,QByteArray("length"));
    hash.insert(Qt::UserRole+11 ,QByteArray("track"));

    m_currentIndex = -1;

    connect(this, &PlayListModel::playModeChanged, this, &PlayListModel::updatePlayList);
}

void PlayListModel::addItem(int trackId, int count)
{
    Track *track = Track::toId(trackId);
    if(!track) {
        return;
    }

    if(count == 0) {
        count = m_playList.size();
    }

    insertRows(count,1,track);

    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("INSERT INTO playlist (`song_id`, `time`) VALUES ( :trackid , 0)");
    query.bindValue(":trackid",trackId);
    query.exec();
}

int PlayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_playList.count();
}


QVariant PlayListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_playList.size())
        return QVariant();

    Track* item = m_playList.at(index.row());
    if(role == Qt::UserRole) {
        return item->id();
    } else if(role == Qt::UserRole+1) {
        return item->artistName();
    } else if(role == Qt::UserRole+2) {
        return item->artistID();
    } else if(role == Qt::UserRole+3) {
        return item->title();
    } else if(role == Qt::UserRole+4) {
        return item->getFileName();
    } else if(role == Qt::UserRole+5) {
        return item->cover();
    } else if (role == Qt::UserRole+6) {
        return item->album();
    } else if (role == Qt::UserRole+7) {
        return item->comment();
    } else if (role == Qt::UserRole+8) {
        return item->genre();
    } else if (role == Qt::UserRole+9) {
        return item->year();
    } else if (role == Qt::UserRole+10) {
        return item->length();
    } else if (role == Qt::UserRole+11) {
        return item->title();
    }

    return QVariant();
}

bool PlayListModel::insertRows(int position, int rows, Track *item, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        m_playList.insert(position, item);
    }
    endInsertRows();
    return true;
}


bool PlayListModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    if((position+rows) > m_playList.count())
    {
        return false;
    }

    beginRemoveRows(QModelIndex(), position, position+rows-1);
    for (int row = 0; row < rows; ++row) {
        m_playList.removeAt(position);
    }
    endRemoveRows();
    return true;
}

void PlayListModel::setPlayMode(PlayListModel::PlayMode mode)
{
    if(mode != m_playMode) {
        m_playMode = mode;
        emit playModeChanged();
    }
}

void PlayListModel::setRepeatMode(PlayListModel::RepeatMode mode)
{
    if(mode != m_repeatMode) {
        m_repeatMode = mode;
        emit repeatModeChanged();
    }
}

QVariant PlayListModel::get(int idx)
{
    if(idx >= m_playList.size())
    {
        return QVariant();
    }

    QMap<QString, QVariant> itemData;
    Track* item = m_playList.at(idx);

    itemData.insert("trackId",item->id());
    itemData.insert("artist",item->artistName());
    itemData.insert("artist_id",item->artistID());
    itemData.insert("title",item->title());
    itemData.insert("fileName",item->getFileName());
    itemData.insert("cover",item->cover());
    itemData.insert("album", item->album());
    itemData.insert("comment", item->comment());
    itemData.insert("genre", item->genre());
    itemData.insert("year", item->year());
    itemData.insert("length",item->length());
    itemData.insert("track",item->title());

    return QVariant(itemData);
}

void PlayListModel::remove(int idx)
{
    removeRows(idx,1);
}

void PlayListModel::clearPlaylist()
{
    qDebug() << "Clear playlist";
    beginRemoveRows(QModelIndex(),0,m_playList.count());
    m_playList.clear();

    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    bool ok = query.exec("DELETE FROM playlist");

    endRemoveRows();
    m_currentIndex = -1;

    if(!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}

void PlayListModel::updatePlayList()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    QString queryString;
    int currentTrackId = 0;
    int currentArtistId = 0;

    QString currentAlbum = "";
    QString currentDir = "/";

    if(m_currentIndex > 0) {
        Track* currentTrack = m_playList.at(m_currentIndex);
        QFileInfo trackFile(currentTrack->getFileName());
        currentTrackId = currentTrack->id();
        currentAlbum = currentTrack->album();
        currentArtistId = currentTrack->artistID();
        currentDir = trackFile.absoluteDir().path();
    }

    switch (m_playMode) {
    case PlayMode::Random:
        queryString = "SELECT id FROM tracks \
                        WHERE id <> "+QString::number(currentTrackId)+" \
                        ORDER BY RANDOM() \
                LIMIT 10";
        break;
    case PlayMode::Artist:
        queryString = "SELECT id FROM tracks \
                        WHERE artist_id = " + QString::number(currentArtistId) + " \
                        AND id <> "+ QString::number(currentTrackId) + " \
                        ORDER BY titile ASC \
                LIMIT 10";
        break;
    case PlayMode::ArtistShuffle:
        queryString = "SELECT id FROM tracks \
                        WHERE artist_id = " + QString::number(currentArtistId) + " \
                        AND id <> "+ QString::number(currentTrackId) + " \
                        ORDER BY RANDOM() \
                LIMIT 10";
        break;
    case PlayMode::Album:
        queryString = "SELECT id FROM tracks \
                        WHERE album = " + QString(currentAlbum) + " \
                        AND id <> "+ QString::number(currentTrackId) + " \
                        ORDER BY num ASC \
                LIMIT 10";
        break;
    case PlayMode::AlbumShuffle:
        queryString = "SELECT id FROM tracks \
                        WHERE album = " + QString(currentAlbum) + " \
                        AND id <> "+ QString::number(currentTrackId) + " \
                        ORDER BY RANDOM() \
                LIMIT 10";
        break;
    case PlayMode::Directory:
        queryString = "SELECT id FROM tracks \
                        WHERE filename LIKE \"%" + QString(currentDir) + "%\" \
                        AND id <> "+ QString::number(currentTrackId) + " \
                        ORDER BY filename ASC \
                LIMIT 10";
        break;
    case PlayMode::DirectoryShuffle:
        queryString = "SELECT id FROM tracks \
                        WHERE filename LIKE \"%" + QString(currentDir) + "%\" \
                        AND id <> "+ QString::number(currentTrackId) + " \
                        ORDER BY RANDOM() \
                LIMIT 10";
        break;
    }

    qDebug() << queryString;

    bool ok = query.exec(queryString);
    if(!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    } else {
        while(query.next()) {
            addItem(query.value(0).toInt());
        }
    }
}

void PlayListModel::loadPlaylistFromDB()
{
    m_playList.clear();
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    bool ok = false;

    int i = 0;
    int ci = -1;
    /*Load preview unfinifed playing song*/
    query.prepare("SELECT * FROM playlist ORDER BY id ASC");
    ok = query.exec();
    if(!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    } else {
        while(query.next()) {
            Track* item = Track::toId(query.value(1).toInt());
            if(!item) {
                continue;
            }

            if(ci == -1 && query.value(2).toUInt() == 0) {
                ci = i;
            }
            m_playList.push_back(item);
            i++;
        }
    }

    if(ci != -1) {
        setCurrentIndex(ci);
    }
}

void PlayListModel::setCurrentIndex(int currentIndex)
{
    if(currentIndex >= 0 && currentIndex < m_playList.count() && currentIndex != m_currentIndex)
    {
        m_currentIndex = currentIndex;
        emit currentIndexChanged(m_currentIndex);

        uint currentPlayId = m_playList.at(currentIndex)->id();
        QSqlDatabase db = dbAdapter::instance().getDatabase();
        QSqlQuery query(db);
        query.prepare("UPDATE playlist SET `time` = :time WHERE song_id=:trackid AND time = 0");
        query.bindValue(":trackid",currentPlayId);
        query.bindValue(":time", QDateTime::currentMSecsSinceEpoch());

        bool ok = query.exec();
        if(!ok)
        {
            qDebug() << query.lastQuery() << query.lastError().text();
        }
    }
}

