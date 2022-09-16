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

#include "track.h"
#include "audiofile.h"

Track::Track(const QString file, QObject* parent)
    : QObject(parent)
    , m_artist("")
    , m_title("")
    , m_album("")
    , m_genre("")
    , m_cover("")
    , m_number(0)
    , m_year(0)
    , m_comment("")
    , m_fileName(file)
    , m_length(0)
    , m_startTime(0)
    , m_endTime(0)
{
    if (!file.isEmpty()) {
        QFile trackFile(file);
        if (!trackFile.exists()) {
            emit trackFileNotFound();
            qDebug() << "File " << file << " not found";
        } else {
            qDebug() << "Add file: " << file;
            m_fileName = file;
            AudioFile* trackFile = new AudioFile(m_fileName);

            if (!trackFile->isValid) {
                emit trackFileNotFound();
                qDebug() << "File " << file << " is bad";
                delete (trackFile);
                return;
            } else {
                qDebug() << trackFile->artist << trackFile->album;
            }

            m_artist = trackFile->artist;
            m_title = trackFile->title;
            m_album = trackFile->album;
            m_genre = trackFile->genre;
            m_comment = trackFile->comment;
            m_number = trackFile->track;
            m_year = trackFile->year;

            m_length = trackFile->length;
        }
    }
}

void Track::setArtist(const QString artist)
{
    if (artist != m_artist) {
        m_artist = artist;
        emit artistChanged();
    }
}

void Track::setTitle(const QString title)
{
    if (title != m_title) {
        m_title = title;
        emit titleChanged();
    }
}

void Track::setAlbum(const QString album)
{
    if (album != m_album) {
        m_album = album;
        emit albumChanged();
    }
}

void Track::setGenre(const QString genre)
{
    if (genre != m_genre) {
        m_genre = genre;
        emit genreChanged();
    }
}

void Track::setNum(const int num)
{
    if (num != m_number) {
        m_number = num;
        emit numChanged();
    }
}

void Track::setYear(const int year)
{
    if (year != m_year) {
        m_year = year;
        emit yearChanged();
    }
}

void Track::setComment(const QString comment)
{
    if (comment != m_comment) {
        m_comment = comment;
        emit commentChanged();
    }
}

void Track::setCover(const QString coverFile)
{
    if (coverFile != m_cover) {
        m_cover = coverFile;
        emit coverChanged();
    }
}
