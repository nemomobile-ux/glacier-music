/*
 * Copyright (C) 2022 Chupligin Sergey <neochapay@gmail.com>
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

#include "localsourceplugin.h"
#include "collection.h"

#include <QDebug>

LocalSourcePlugin::LocalSourcePlugin(QObject* parent)
    : m_tracksModel(nullptr)
    , m_hasBack(false)
    , m_hasForward(false)
{
    m_tracksModel = new TracksModel();

    Collection* collection = new Collection();
    collection->rescanCollection();

    connect(m_tracksModel, &TracksModel::modelReset, this, &LocalSourcePlugin::calcButtonStatus);
    connect(m_tracksModel, &TracksModel::currentIndexChanged, this, &LocalSourcePlugin::makeTrackPlayed);
    connect(collection, &Collection::rescanCollectionFinished, this, &LocalSourcePlugin::complementPlayList);
}

bool LocalSourcePlugin::hasBack()
{
    return m_hasBack;
}

void LocalSourcePlugin::setHasBack(bool hasBack)
{
}

bool LocalSourcePlugin::hasForward()
{
    return m_hasForward;
}

void LocalSourcePlugin::setHasForward(bool hasForward)
{
}

TracksModel* LocalSourcePlugin::tracksModel()
{
    return m_tracksModel;
}

void LocalSourcePlugin::loadPlaylist(PlayMode mode, QString param)
{
    loadCurrentPlayList();
    calcButtonStatus();
}

void LocalSourcePlugin::clearPlaylist()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    if (query.exec("DELETE FROM playlist WHERE time = 0")) {
        m_tracksModel->reset();
    }
}

void LocalSourcePlugin::calcButtonStatus()
{
    bool hasBack = m_tracksModel->currentIndex() > 0;
    bool hasForward = m_tracksModel->currentIndex() < m_tracksModel->rowCount();

    if (hasBack != m_hasBack) {
        m_hasBack = hasBack;
        emit hasBackChanged();
    }

    if (hasForward != m_hasForward) {
        m_hasForward = hasForward;
        emit hasForwardChanged();
    }
}

void LocalSourcePlugin::loadCurrentPlayList()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    QString queryString = "SELECT tracks.fileName FROM playlist "
                          "INNER JOIN tracks ON playlist.song_id = tracks.id "
                          "WHERE time = 0 "
                          "ORDER by playlist.id ASC";

    bool ok = query.exec(queryString);
    if (!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    } else {
        while (query.next()) {
            Track* track = new Track(query.value(0).toString());
            if (track != nullptr) {
                m_tracksModel->addTrack(track);
            }
        }
    }
}

void LocalSourcePlugin::complementPlayList()
{
    if (m_tracksModel->rowCount() < 20) {
        QString queryString;
        QString fileName = "";

        QSqlDatabase db = dbAdapter::instance().getDatabase();
        QSqlQuery query(db);

        int limit = 20 - m_tracksModel->rowCount();

        Track* currentTrack = m_tracksModel->getTrack(m_tracksModel->currentIndex());
        if (currentTrack != nullptr) {
            fileName = currentTrack->getFileName();
        }

        queryString = "SELECT fileName FROM tracks \
                WHERE filename <> '"
            + fileName + "' \
                ORDER BY RANDOM() \
                LIMIT "
            + QString::number(limit);

        bool ok = query.exec(queryString);
        if (!ok) {
            qDebug() << query.lastQuery() << query.lastError().text();
        } else {
            while (query.next()) {
                Track* track = new Track(query.value(0).toString());
                m_tracksModel->addTrack(track);
            }
        }
    }
}

void LocalSourcePlugin::makeTrackPlayed(int id)
{
    Track* currentTrack = m_tracksModel->getTrack(id);
    if (currentTrack == nullptr) {
        return;
    }
    QString currentTrackFileName = currentTrack->getFileName();

    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    query.prepare("UPDATE playlist SET time = :time "
                  "WHERE time = 0 "
                  "AND song_id = (SELECT id FROM tracks WHERE fileName = '"
        + currentTrackFileName + "') "
                                 "ORDER BY id ASC "
                                 "LIMIT 1");
    query.bindValue(":time", QDateTime::currentMSecsSinceEpoch());
    bool ok = query.exec();
    if (!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    calcButtonStatus();
}
