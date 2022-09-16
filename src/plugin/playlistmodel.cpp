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

PlayListModel::PlayListModel(QObject *parent) :
    QAbstractListModel(parent)
  , m_playMode(PlayMode::Random)
  , m_repeatMode(RepeatMode::NoneRepeat)
{
    hash.insert(Qt::UserRole ,QByteArray("artist"));
    hash.insert(Qt::UserRole+1 ,QByteArray("title"));
    hash.insert(Qt::UserRole+2 ,QByteArray("fileName"));
    hash.insert(Qt::UserRole+3 ,QByteArray("cover"));
    hash.insert(Qt::UserRole+4 ,QByteArray("album"));
    hash.insert(Qt::UserRole+5 ,QByteArray("comment"));
    hash.insert(Qt::UserRole+6 ,QByteArray("genre"));
    hash.insert(Qt::UserRole+7 ,QByteArray("year"));
    hash.insert(Qt::UserRole+8 ,QByteArray("length"));
    hash.insert(Qt::UserRole+9 ,QByteArray("track"));
}

void PlayListModel::addItem(Track* track)
{
    insertRows(1,1,track);
}

int PlayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_playList.count();
}

QVariant PlayListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_playList.size())
        return QVariant();

    Track* item = m_playList.at(index.row());
    if(role == Qt::UserRole) {
        return item->artist();
    } else if(role == Qt::UserRole+1) {
        return item->title();
    } else if(role == Qt::UserRole+2) {
        return item->getFileName();
    } else if(role == Qt::UserRole+3) {
        return item->cover();
    } else if (role == Qt::UserRole+4) {
        return item->album();
    } else if (role == Qt::UserRole+5) {
        return item->comment();
    } else if (role == Qt::UserRole+6) {
        return item->genre();
    } else if (role == Qt::UserRole+7) {
        return item->year();
    } else if (role == Qt::UserRole+8) {
        return item->length();
    } else if (role == Qt::UserRole+9) {
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
    if((position+rows) > m_playList.count()) {
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
    if(idx >= m_playList.size()) {
        return QVariant();
    }

    QMap<QString, QVariant> itemData;
    Track* item = m_playList.at(idx);

    itemData.insert("artist",item->artist());
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
    beginResetModel();
    m_playList.clear();
    endResetModel();
}

