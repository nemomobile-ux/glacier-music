/*
 * Copyright (C) 2022-2025 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef MUSICSOURCEPLUGIN_H
#define MUSICSOURCEPLUGIN_H

#include "glaciermusic_global.h"
#include "tracksmodel.h"

#include <QAbstractListModel>
#include <QObject>

class GLACIERMUSIC_EXPORT MusicSourcePlugin : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool hasBack READ hasBack WRITE setHasBack NOTIFY hasBackChanged)
    Q_PROPERTY(bool hasForward READ hasForward WRITE setHasForward NOTIFY hasForwardChanged)

public:
    enum PlayMode {
        Random,
        Artist,
        ArtistShuffle,
        Album,
        AlbumShuffle,
        Directory,
        DirectoryShuffle,
        Smart
    };
    Q_ENUMS(PlayMode)

    virtual ~MusicSourcePlugin() { };
    virtual bool enabled() = 0;
    virtual QString name() = 0;
    virtual QString id() = 0;

    virtual bool hasBack() = 0;
    virtual void setHasBack(bool hasBack) = 0;

    virtual bool hasForward() = 0;
    virtual void setHasForward(bool hasForward) = 0;

    virtual TracksModel* tracksModel() = 0;
    virtual void loadPlaylist(PlayMode mode, QString param = "") = 0;
    virtual void clearPlaylist() = 0;

signals:
    void pluginChanged(QString id);

    void hasBackChanged();
    void hasForwardChanged();
};

Q_DECLARE_INTERFACE(MusicSourcePlugin, "GlacierMusic.SourcePlugin")

#endif // MUSICSOURCEPLUGIN_H
