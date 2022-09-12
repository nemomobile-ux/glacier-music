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

#include <QObject>
#include <QMediaPlayer>
#include <QSettings>

#include "cover.h"

class GlacierMusicPlayer : public QMediaPlayer
{
    Q_OBJECT
    Q_PROPERTY(bool firstRun READ firstRun)
    Q_PROPERTY(QString cover READ cover NOTIFY coverChanged)

public:
    explicit GlacierMusicPlayer(QObject *parent = nullptr);
    ~GlacierMusicPlayer();
    bool firstRun() {return false;}

    QString cover();

signals:
    void noMusicFiles();
    void noSourcePlugins();
    void coverChanged();

private slots:
    void setDefaultCover();

private:
    QSettings* m_settings;
    Cover* m_coverAdapter;

    QString m_coverPath;
};

#endif // GLACIERMUSICPLAYER_H
