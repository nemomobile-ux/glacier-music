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

#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "track.h"

class PlayListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(PlayMode playMode READ playMode WRITE setPlayMode NOTIFY playModeChanged)
    Q_PROPERTY(RepeatMode repeatMode READ repeatMode WRITE setRepeatMode NOTIFY repeatModeChanged)

public:
    enum PlayMode {
        Random,
        Artist,
        ArtistShuffle,
        Album,
        AlbumShuffle,
        Directory,
        DirectoryShuffle,
        // Smart @todo
    };
    Q_ENUMS(PlayMode)

    enum RepeatMode {
        NoneRepeat,
        RepeatAll,
        RepeatOne
    };
    Q_ENUMS(RepeatMode)

    explicit PlayListModel(QObject* parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const { return hash; }

    bool insertRows(int position, int rows, Track* item, const QModelIndex& index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex());

    PlayMode playMode() { return m_playMode; }
    void setPlayMode(PlayMode mode);

    RepeatMode repeatMode() { return m_repeatMode; }
    void setRepeatMode(RepeatMode mode);

public slots:
    void clearPlaylist();
    void addItem(Track* track);
    QVariant get(const int idx);
    void remove(const int idx);

signals:
    void playListUpdate();
    void currentIndexChanged(int currentIndex);
    void playModeChanged();
    void repeatModeChanged();

private:
    QHash<int, QByteArray> hash;
    QList<Track*> m_playList;
    PlayMode m_playMode;
    RepeatMode m_repeatMode;
};

#endif // PLAYLISTMODEL_H
