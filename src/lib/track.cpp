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
#include "dbadapter.h"
#include "audiofile.h"

Track::Track(const QString file, QObject *parent) : QObject(parent)
    , m_id(0)
    , m_title("")
    , m_album("")
    , m_genre("")
    , m_cover("")
    , m_number(0)
    , m_year(0)
    , m_comment("")
    , m_fileName(file)
    , m_length(0)
    , m_artist(new Artist(0))
    , m_startTime(0)
    , m_endTime (0)
{
    QFile trackFile(file);
    if(!trackFile.exists())
    {
        emit trackFileNotFound();
        qDebug() << "File " << file << " not found";
        return;
    }
    else
    {
        qDebug() << "Add file: " << file;
        m_fileName = file;
        AudioFile *trackFile = new AudioFile(m_fileName);

        if(!trackFile->isValid)
        {
            emit trackFileNotFound();
            qDebug() << "File " << file << " is bad";
            delete(trackFile);
            return;
        }
        else
        {
            qDebug() << trackFile->artist << trackFile->album;
        }

        Artist *newArtist = new Artist(trackFile->artist);
        uint artistId = newArtist->id();
        if(artistId == 0)
        {
            artistId = newArtist->create(trackFile->artist);
            newArtist = new Artist(artistId);
        }

        if(artistId == 0) {
            qWarning() << "Empty artist";
        }

        m_artist = newArtist;
        m_title = trackFile->title;
        m_album = trackFile->album;
        m_genre = trackFile->genre;
        m_comment = trackFile->comment;
        m_number = trackFile->track;
        m_year = trackFile->year;

        m_length = trackFile->length;

        QSqlDatabase db = dbAdapter::instance().getDatabase();
        QSqlQuery query(db);
        query.prepare("SELECT id, "
                      "artist_id,"
                      "title,"
                      "album,"
                      "comment,"
                      "genre,"
                      "cover,"
                      "track,"
                      "year "
                      "FROM tracks WHERE filename=:fileName");
        query.bindValue(":fileName",m_fileName);

        bool ok = query.exec();
        if(!ok)
        {
            qDebug() << query.lastQuery() << query.lastError().text();
        }
        /*If file exists and in database check IDv3 tags and database tags*/
        if(query.next())
        {
            m_id = query.value(0).toInt();
            uint artist_id = query.value(1).toInt();
            QString title = query.value(2).toString();
            QString album = query.value(3).toString();
            QString comment = query.value(4).toString();
            QString genre = query.value(5).toString();

            int number = query.value(7).toInt();
            int year = query.value(8).toInt();

            if(artist_id != m_artist->id()
                    || title != m_title
                    || album != m_album
                    || genre != m_genre
                    || comment != m_comment
                    || number != m_number
                    || year != m_year)
            {
                update();
            }
            m_cover = query.value(6).toString();
            QFile cf(m_cover);
            if(!cf.exists()) {
                m_cover = "";
            }
        }
        else
        {
            m_id = insert();
        }

        if(!m_id)
        {
            return;
        }
    }
}

Track* Track::toId(const int trackId)
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT filename FROM tracks WHERE id=:id");
    query.bindValue(":id",trackId);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return 0;
    }

    if(query.next())
    {
        QString fileName = query.value(0).toString();
        Track* track = new Track(fileName);

        return track;
    }
    return 0;
}

void Track::setTitle(const QString title)
{
    if(title != m_title) {
        m_title = title;
        update();
        emit titleChanged();
    }
}

void Track::setAlbum(const QString album)
{
    if(album != m_album) {
        m_album = album;
        update();
        emit albumChanged();
    }
}

void Track::setGenre(const QString genre)
{
    if(genre != m_genre) {
        m_genre = genre;
        update();
        emit genreChanged();
    }
}

void Track::setNum(const int num)
{
    if(num != m_number) {
        m_number = num;
        update();
        emit numChanged();
    }
}

void Track::setYear(const int year)
{
    if(year != m_year) {
        m_year = year;
        update();
        emit yearChanged();
    }
}

void Track::setComment(const QString comment)
{
    if(comment != m_comment) {
        m_comment = comment;
        update();
        emit commentChanged();
    }
}

void Track::setArtistName(const QString name)
{
    if(m_artist->id() == 0) {
        return;
    }

    m_artist->setTitle(name);
}

void Track::setCover(const QString coverFile)
{
    if(coverFile != m_cover)
    {
        m_cover = coverFile;
        update();
    }
}

int Track::insert()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    query.prepare("INSERT INTO tracks (`artist_id`, `filename`, `title`, `album`, `comment`, `genre`, `track`, `year`, `length`) \
                                 VALUES (:artistid, :filename, :title, :album, :comment, :genre, :track, :year, :length)");
    query.bindValue(":artistid",m_artist->id());
    query.bindValue(":filename",m_fileName);
    query.bindValue(":title",m_title);
    query.bindValue(":album",m_album);
    query.bindValue(":comment",m_comment);
    query.bindValue(":genre",m_genre);
    query.bindValue(":track",m_number);
    query.bindValue(":year",m_year);
    query.bindValue(":length",m_length);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return -1;
    }
    return query.lastInsertId().toInt();
}

void Track::update()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("UPDATE tracks SET artist_id=:AID,title=:Title,track=:Track,album=:Album,comment=:Comment,genre=:Genre,cover=:Cover,year=:Year WHERE id=:rid");
    query.bindValue(":AID",m_artist->id());
    query.bindValue(":Title",m_title);
    query.bindValue(":Track",m_number);
    query.bindValue(":Album",m_album);
    query.bindValue(":Comment",m_comment);
    query.bindValue(":Cover",m_cover);
    query.bindValue(":Genre",m_genre);
    query.bindValue(":Year",m_year);
    query.bindValue(":rid",m_id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        AudioFile audioFile(m_fileName);
        if(audioFile.isValid)
        {
            audioFile.artist = m_artist->title();
            audioFile.title = m_title;
            audioFile.album = m_album;
            audioFile.comment = m_comment;
            audioFile.genre = m_genre;
            audioFile.track = m_number;
            audioFile.year = m_year;

            audioFile.sync();
        }
    }
}

void Track::remove()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("DELETE FROM tracks WHERE id=:id");
    query.bindValue(":id",m_id);

    bool ok = query.exec();

    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    else
    {
        QFile* file = new QFile(m_fileName);
        if(file->exists())
        {
            file->remove();
        }

        if(m_artist->trackCount() == 0)
        {
            m_artist->remove();
        }
    }
}
/*
Return trackId if file in DB or 0 if file is new
*/
int Track::getTrackIdFromFileName(QString fileName)
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT id FROM tracks WHERE filename=:filename");
    query.bindValue(":filename",fileName);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return 0;
    }

    if(query.next())
    {
        int trackId = query.value(0).toInt();
        return trackId;
    }
    return 0;
}
