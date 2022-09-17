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

#ifndef GLACIERMUSICPLAYER_H
#define GLACIERMUSICPLAYER_H

#include <QMediaPlayer>
#include <QObject>
#include <QSettings>

#include "cover.h"
#include "sourcepluginmanager.h"

class GlacierMusicPlayer : public QMediaPlayer {
    Q_OBJECT
    Q_PROPERTY(bool firstRun READ firstRun CONSTANT)
    Q_PROPERTY(QString cover READ cover NOTIFY coverChanged)

    Q_PROPERTY(bool hasBack READ hasBack NOTIFY hasBackChanged)
    Q_PROPERTY(bool hasForward READ hasForward NOTIFY hasForwardChanged)

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

    Q_PROPERTY(QAbstractListModel* trackModel READ trackModel NOTIFY trackModelChanged)

public:
    explicit GlacierMusicPlayer(QObject* parent = nullptr);
    ~GlacierMusicPlayer();
    bool firstRun() { return false; }

    QString cover();

    bool hasBack() { return m_hasBack; }
    bool hasForward() { return m_hasForward; }

    Q_INVOKABLE void playPrev();
    Q_INVOKABLE void playForward();

    QString source() { return m_source; }
    void setSource(QString source);

    Q_INVOKABLE QAbstractListModel* trackModel();
    Q_INVOKABLE QString getCover(QString artist, QString track, QString album);

signals:
    void noMusicFiles();
    void noSourcePlugins();
    void coverChanged();

    void hasBackChanged();
    void hasForwardChanged();

    void sourceChanged();

    void trackModelChanged();

private slots:
    void setDefaultCover();
    void onHasBackChanged();
    void onHasForwardChanged();

private:
    QSettings* m_settings;
    Cover* m_coverAdapter;

    QString m_coverPath;

    MusicSourcePlugin* m_sourcePlugin;

    bool m_hasBack;
    bool m_hasForward;

    QString m_source;
    QAbstractListModel* m_trackModel;
};

#endif // GLACIERMUSICPLAYER_H
