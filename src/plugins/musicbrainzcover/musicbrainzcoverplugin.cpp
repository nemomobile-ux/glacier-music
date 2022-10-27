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

#include "musicbrainzcoverplugin.h"
#include "musicbrainzconnect.h"

MusicBrainzCoverPlugin::MusicBrainzCoverPlugin()
    : m_track(nullptr)
{
}

void MusicBrainzCoverPlugin::getCover(Track* track)
{
    if (track == m_track || track == nullptr) {
        return;
    }

    if (track->artist().isEmpty() || track->title().isEmpty()) {
        return;
    }

    m_track = track;

    /*Trying get cover from musicbrainz*/
    MusicBrainzConnect* mbConnect = new MusicBrainzConnect();
    mbConnect->getData(track->artist(), track->title());
    connect(mbConnect, &MusicBrainzConnect::coverReady, this, &MusicBrainzCoverPlugin::onCoverReady);
    connect(mbConnect, &MusicBrainzConnect::downloadCover, this, &MusicBrainzCoverPlugin::coverLoaing);
}

void MusicBrainzCoverPlugin::onCoverReady(QString coverFilePath)
{
    QImage cover(coverFilePath);
    if (!cover.isNull() && m_track != nullptr) {
        m_track->setCover(cover);
    }
}
