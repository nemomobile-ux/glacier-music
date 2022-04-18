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


#ifndef ARTIST_H
#define ARTIST_H

#include "dbadapter.h"

class Artist : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint id READ id NOTIFY idChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(uint trackCount READ trackCount NOTIFY trackCountChanged)

public:
    explicit Artist(uint id, QObject *parent = nullptr);
    explicit Artist(QString title, QObject *parent = nullptr);
    uint getId(QString name);

    uint id() {return m_id;}
    uint trackCount() {return m_trackCount;}

    QString title() {return  m_title;}
    void setTitle(QString title);

    uint create(QString title);
    void remove();

signals:
    void idChanged();
    void titleChanged();
    void trackCountChanged();

    void idNotFound();
    void titleNotFound();

private:
    uint m_id;
    uint m_trackCount;
    QString m_title;

    void calcTrackCount();
};
#endif // ARTIST_H
