/*
 * Copyright (C) 2021-2025 Chupligin Sergey <neochapay@gmail.com>
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

#include <QImage>
#include <QtCore>
#include <artist.h>

class Artist;

class Track : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY trackChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY trackChanged)
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY trackChanged)
    Q_PROPERTY(QString genre READ genre WRITE setGenre NOTIFY trackChanged)
    Q_PROPERTY(int num READ num WRITE setNum NOTIFY trackChanged)
    Q_PROPERTY(int year READ year WRITE setYear NOTIFY trackChanged)
    Q_PROPERTY(int length READ length CONSTANT)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY trackChanged)
    Q_PROPERTY(QImage cover READ cover WRITE setCover NOTIFY trackChanged)

public:
    explicit Track(const QString file = "");

    QString artist() { return m_artist; }
    QString title() { return m_title; }
    QString album() { return m_album; }
    QString genre() { return m_genre; }
    int num() { return m_number; }
    int year() { return m_year; }
    int length() { return m_length; }
    QString comment() { return m_comment; }
    QImage cover() { return m_cover; }

    QString getFileName() { return m_fileName; }

    void setArtist(const QString artist);
    void setTitle(const QString title);
    void setAlbum(const QString album);
    void setGenre(const QString genre);
    void setNum(const int num);
    void setYear(const int year);
    void setComment(const QString comment);
    void setArtistName(const QString name);
    void setCover(const QImage cover);

signals:
    void trackFileNotFound();
    void trackChanged();

private:
    QString m_artist;
    QString m_title;
    QString m_album;
    QString m_genre;
    int m_number;
    int m_year;
    QString m_comment;
    QImage m_cover;
    QString m_fileName;
    int m_length;

    uint m_startTime;
    uint m_endTime;
};
#endif // TRACK_H
