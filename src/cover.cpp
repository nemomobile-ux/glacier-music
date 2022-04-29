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

#include "cover.h"
#include "audiofile.h"
#include "musicbrainzconnect.h"

Cover::Cover(QObject *parent) : QObject(parent)
  ,m_coverDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/covers")
{
    QDir coverDir(m_coverDir);
    if(!coverDir.exists()) {
        coverDir.mkpath(m_coverDir);
    }
}

void Cover::getCoverByTrackId(int trackId)
{
    m_track = Track::toId(trackId);
    if(!m_track)
    {
        return;
    }

    QString artist = m_track->artistName();
    QString title = m_track->title();
    QString cover = m_track->cover();

    QFile coverFile(cover);

    if(cover.isEmpty() || !coverFile.exists())
    {
        /*Search cover to tags*/
        AudioFile file(m_track->getFileName());
        QImage coverImgFromTags = file.coverImg();
        if(!coverImgFromTags.isNull()) {
            QString coverPath = m_coverDir+"/"+artist+"_"+title+".jpg";
            coverImgFromTags.save(coverPath,"jpg",100);
            qDebug() << "We have cover in tag. Save to " << coverPath ;
            m_coverReady(coverPath);
            return;
        }

        /*Search cover image in file folder*/
        QFileInfo musicFileInfo(m_track->getFileName());
        QString musicFileDir = musicFileInfo.absoluteDir().absolutePath();
        QFile localCover(musicFileDir+"/cover.jpg");
        if(localCover.exists())
        {
            m_coverReady(musicFileDir+"/cover.jpg");
            return;
        }

        /*Trying get cover from musicbrainz*/
        MusicBrainzConnect *mbConnect = new MusicBrainzConnect();
        mbConnect->getData(artist,title);
        connect(mbConnect,SIGNAL(coverReady(QString)),this,SLOT(m_coverReady(QString)));
        connect(mbConnect,SIGNAL(downloadCover()),this,SIGNAL(coverLoaing()));
    }
    else
    {
        m_coverReady(cover);
    }
}

void Cover::m_coverReady(QString coverFile)
{
    QFile cf(coverFile);
    if(cf.exists()) {
        m_track->setCover(coverFile);
        emit coverReady(coverFile);
    } else {
        qWarning() << "Cover file" << coverFile << "not exist";
    }
}
