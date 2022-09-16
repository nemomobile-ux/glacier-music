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

#include "glaciermusicplayer.h"

GlacierMusicPlayer::GlacierMusicPlayer(QObject* parent)
    : QMediaPlayer(parent)
    , m_settings(new QSettings)
    , m_coverAdapter(new Cover)
    , m_plugin(nullptr)
{
    SourcePluginManager* sources = new SourcePluginManager();
    if (sources->getPlugins().empty()) {
        qWarning() << "dont have sources plugin";
        return;
    }
    //@todo: Fixup loading plugin
    m_plugin = sources->getPlugins().first();

    setVolume(m_settings->value("volume").toInt());

    connect(m_coverAdapter, &Cover::coverLoaing, this, &GlacierMusicPlayer::setDefaultCover);
    connect(m_plugin, &MusicSourcePlugin::hasBackChanged, this, &GlacierMusicPlayer::hasBackChanged);
    connect(m_plugin, &MusicSourcePlugin::hasForwardChanged, this, &GlacierMusicPlayer::hasForwardChanged);

    delete (sources);
}

GlacierMusicPlayer::~GlacierMusicPlayer()
{
    m_settings->setValue("volume", volume());
    m_settings->setValue("seek", position());
    m_settings->setValue("playbackState", state());
    m_settings->sync();
}

QString GlacierMusicPlayer::cover()
{
    QString cover = "/usr/share/glacier-music/images/cover.png";
    return cover;
}

bool GlacierMusicPlayer::hasBack()
{
    if (m_plugin != nullptr) {
        return m_plugin->hasBack();
    }
    return false;
}

bool GlacierMusicPlayer::hasForward()
{
    if (m_plugin != nullptr) {
        return m_plugin->hasForward();
    }
    return false;
}

void GlacierMusicPlayer::playPrev()
{
    //@todo
}

void GlacierMusicPlayer::playForward()
{
    //@todo
}

void GlacierMusicPlayer::setDefaultCover()
{
    QString cover = "/usr/share/glacier-music/images/cover.png";
    if (cover != m_coverPath) {
        m_coverPath = cover;
        emit coverChanged();
    }
}
