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

#ifndef TRACK_H
#define TRACK_H

#include <QtCore>
#include <artist.h>
#include "item.h"

class Artist;

class Track : public Item
{
    Q_OBJECT
public:
    Track(const QString file);

    Artist* getArtist() {return m_artist;}
    void setArtist(Artist *artist) {m_artist = artist;}

    Q_INVOKABLE static Track* toId(const int trackId);
    Q_INVOKABLE const QString getTitle() {return m_title;}
    Q_INVOKABLE const QString getAlbum() {return m_album;}
    Q_INVOKABLE const QString getGenre() {return m_genre;}
    Q_INVOKABLE const QString getCover() {return m_cover;}
    Q_INVOKABLE const QString getComment() {return m_comment;}

public slots:
    int getArtistId() {return m_artist_id;}
    QString getArtistName(){return m_artist->title() ;}
    QString getFileName(){return m_fileName;}
    int getNumber() {return m_number;}
    int getYear() {return m_year;}
    int getLength() {return m_length;}

    void setTitle(const QString title) {m_title = title;}
    void setAlbum(const QString album) {m_album = album;}
    void setGenre(const QString genre) {m_genre = genre;}
    void setNum(const int num) {m_number = num;}
    void setYear(const int year) {m_year = year;}
    void setLength(const int length) {m_length = length;}
    void setComment(const QString comment) {m_comment = comment;}
    void setArtistName(const QString name);
    void setCover(const QString coverFile);

    int insert();
    void update();
    void remove();

signals:
    void titleChanged();
    void trackFileNotFound();

private:
    int getTrackIdFromFileName(const QString fileName);

    int m_id;
    int m_artist_id;
    QString m_title;
    QString m_album;
    QString m_genre;
    QString m_cover;
    int m_number;
    int m_year;
    QString m_comment;
    QString m_fileName;
    int m_length;

    Artist *m_artist;
    bool m_played;

    uint m_startTime;
    uint m_endTime;
};
#endif // TRACK_H
