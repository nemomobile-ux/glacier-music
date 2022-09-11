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

#include "artist.h"
#include "track.h"

Artist::Artist(uint id, QObject *parent) : QObject(parent)
    , m_id(0)
    , m_trackCount(0)
    , m_title("")
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT name FROM artist WHERE id=:id");
    query.bindValue(":id",id);

    bool ok = query.exec();
    if(!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    if(query.next()) {
        m_id = id;
        m_title = query.value(0).toString();
        calcTrackCount();
    } else {
        emit idNotFound();
    }
}

Artist::Artist(QString title, QObject *parent) : QObject(parent)
  , m_id(0)
  , m_trackCount(0)
  , m_title("")
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT id FROM artist WHERE name=:title");
    query.bindValue(":title",title);

    bool ok = query.exec();
    if(!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    if(query.next()) {
        m_title = title;
        m_id = query.value(0).toUInt();
        calcTrackCount();
    } else {
        emit titleNotFound();
    }

}

void Artist::setTitle(QString title)
{
    if(title == m_title) {
        return;
    }

    Artist *a = new Artist(title);
    if(a->id() == 0) {
/*New name*/
        QSqlDatabase db = dbAdapter::instance().getDatabase();
        QSqlQuery query(db);
        query.prepare("UPDATE artist SET name=:name WHERE id=:id");
        query.bindValue(":name",title);
        query.bindValue(":id",m_id);

        bool ok = query.exec();
        if(!ok)
        {
            qDebug() << query.lastQuery() << query.lastError().text();
        }
        emit titleChanged();
    } else {
/*Exist name*/
        /*Delete old item*/
        QSqlDatabase db = dbAdapter::instance().getDatabase();
        QSqlQuery query(db);
        query.prepare("DELETE FROM artist WHERE id=:id");
        query.bindValue(":id",m_id);
        query.exec();

        /*Update artistID on track*/
        query.prepare("UPDATE tracks SET artist_id=:NID WHERE artist_id=:OID");
        query.bindValue(":NID",a->id());
        query.bindValue(":OID",m_id);
        query.exec();

        m_id = a->id();
        m_title = title;

        calcTrackCount();

        emit idChanged();
    }
}

uint Artist::create(QString title)
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    query.prepare("INSERT INTO artist (name) VALUES (:title)");
    query.bindValue(":title",title);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return 0;
    }

    return query.lastInsertId().toInt();
}

void Artist::remove()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("DELETE FROM artist WHERE id=:id");
    query.bindValue(":id",m_id);
    query.exec();

    /*Update artistID on track*/
    query.prepare("UPDATE tracks SET artist_id=0 WHERE artist_id=:AID");
    query.bindValue(":AID",m_id);
    query.exec();
}

void Artist::calcTrackCount()
{
    if(m_id == 0) {
        return;
    }

    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT id FROM tracks WHERE artist_id = :id");
    query.bindValue(":id",m_id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
    query.last();
    uint count = query.at()+1;
    if(count != m_trackCount) {
        emit trackCountChanged();
    }
}
