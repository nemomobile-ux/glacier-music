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
#include "coversourceplugin.h"

GlacierMusicPlayer::GlacierMusicPlayer(QObject* parent)
    : QMediaPlayer(parent)
    , m_settings(new QSettings)
    , m_cover(QImage("/usr/share/glacier-music/images/cover.png"))
    , m_sourcePlugin(nullptr)
    , m_hasBack(false)
    , m_hasForward(false)
    , m_playing(false)
    , m_trackModel(nullptr)
{
    SourcePluginManager* sources = new SourcePluginManager();
    if (sources->getPlugins().empty()) {
        qWarning() << "dont have sources plugin";
        return;
    }

    m_coverPlugin = new CoverPluginManager();
    if (m_coverPlugin->getPlugins().empty()) {
        qWarning() << "Can`t load covers plugin";
    }

    setAudioRole(QAudio::MusicRole);

    //@todo: Fixup loading plugin
    m_sourcePlugin = sources->getPlugins().first();
    m_trackModel = m_sourcePlugin->tracksModel();

    setVolume(m_settings->value("volume").toInt());

    connect(m_sourcePlugin, &MusicSourcePlugin::hasBackChanged, this, &GlacierMusicPlayer::onHasBackChanged);
    connect(m_sourcePlugin, &MusicSourcePlugin::hasForwardChanged, this, &GlacierMusicPlayer::onHasForwardChanged);
    connect(m_trackModel, &TracksModel::currentIndexChanged, this, &GlacierMusicPlayer::onCurrectTrackChanged);
    connect(m_trackModel, &TracksModel::rowsInserted, this, &GlacierMusicPlayer::onTrackAddedToPlayList);
    connect(this, &QMediaPlayer::mediaStatusChanged, this, &GlacierMusicPlayer::onMediaStatusChanged);

    delete (sources);
}

GlacierMusicPlayer::~GlacierMusicPlayer()
{
    m_settings->setValue("volume", volume());
    m_settings->setValue("seek", position());
    m_settings->setValue("playbackState", state());
    m_settings->sync();
}

QImage GlacierMusicPlayer::cover()
{
    return m_cover;
}

void GlacierMusicPlayer::playPrev()
{
    m_trackModel->setCurrentIndex(m_trackModel->currentIndex() - 1);
}

void GlacierMusicPlayer::playForward()
{
    m_trackModel->setCurrentIndex(m_trackModel->currentIndex() + 1);
}

void GlacierMusicPlayer::playPause()
{
    if (state() == State::PlayingState) {
        pause();
        m_playing = false;
    } else {
        if (m_trackModel->rowCount() == 0) {
            m_sourcePlugin->loadPlaylist(MusicSourcePlugin::PlayMode::Random);
            playForward();
        } else if (m_trackModel->currentIndex() == -1) {
            playForward();
        }

        m_playing = true;
        play();
    }
}

void GlacierMusicPlayer::setSource(QString source)
{
    if (source != m_source) {
        m_source = source;
        setMedia(QUrl(m_source));
    }
}

QAbstractListModel* GlacierMusicPlayer::trackModel()
{
    return m_trackModel;
}

void GlacierMusicPlayer::onHasBackChanged()
{
    if (m_hasBack != m_sourcePlugin->hasBack()) {
        m_hasBack = m_sourcePlugin->hasBack();
        emit hasBackChanged();
    }
}

void GlacierMusicPlayer::onHasForwardChanged()
{
    if (m_hasForward != m_sourcePlugin->hasForward()) {
        m_hasForward = m_sourcePlugin->hasForward();
        emit hasForwardChanged();
    }
}

void GlacierMusicPlayer::onCurrectTrackChanged(int currentIndex)
{
    Track* currentTrack = m_trackModel->getTrack(currentIndex);
    if (currentTrack != nullptr) {
        m_cover = currentTrack->cover();
        emit coverChanged();
        setSource("file://" + currentTrack->getFileName());
        if (m_playing) {
            play();
        }
    } else {
        qWarning() << "Wrong track!";
    }
}

void GlacierMusicPlayer::onTrackAddedToPlayList(const QModelIndex& parent, int first, int last)
{
    if (first < 0) {
        first = 0;
    }

    for (int i = first; i <= last; i++) {
        Track* addedTrack = m_trackModel->getTrack(i);
        if (addedTrack != nullptr) {
            foreach (MusicCoverPlugin* plugin, m_coverPlugin->getPlugins()) {
                plugin->getCover(addedTrack);
            }
        }
        if (first == 0) {
            m_trackModel->setCurrentIndex(0);
        }
    }
}

void GlacierMusicPlayer::onMediaStatusChanged(MediaStatus status)
{
    if (m_playing && status == MediaStatus::EndOfMedia) {
        playForward();
    }
}
