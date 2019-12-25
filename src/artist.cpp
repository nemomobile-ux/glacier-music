#include "artist.h"
#include "track.h"
#include "dbadapter.h"

Artist::Artist(QObject *parent) : Item(parent)
{
    m_id = 0;
}

QHash<int, Artist*> Artist::m_cache;

Artist* Artist::toId(const int artistId)
{
    if(m_cache.contains(artistId))
    {
        return m_cache.value(artistId);
    }

    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT name FROM artist WHERE id=:id");
    query.bindValue(":id",artistId);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return nullptr;
    }
    if(query.next())
    {
        Artist* artist = new Artist();
        artist->m_id = artistId;
        artist->m_name = query.value(0).toString();
        m_cache.insert(artistId,artist);

        return artist;
    }
    m_cache.insert(artistId,0);
    return nullptr;
}

int Artist::idFromName(const QString name)
{
    int id = 0;
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);

    query.prepare("SELECT id FROM artist WHERE name=:name");
    query.bindValue(":name",name);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return 0;
    }

    if(query.next())
    {
        id = query.value(0).toInt();
        return id;
    }

    return 0;
}

int Artist::insert()
{
    if(m_name.length() == 0)
    {
        return -1;
    }

    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);

    query.prepare("INSERT INTO artist (name) VALUES (:name)");
    query.bindValue(":name",m_name);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toInt();
}

bool Artist::setName(const QString name)
{
    if(name.length() == 0)
    {
        return false;
    }

    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT id FROM artist WHERE name=:name");
    query.bindValue(":name",name);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return false;
    }

    if(query.next())
    {
        m_id = query.value(0).toInt();
        return false;
    }
    else
    {
        m_oldname = m_name;
        m_name = name;
        if(getTracks().length() > 0 && m_oldname != m_name)
        {
            update();
        }
        return true;
    }
}

void Artist::update()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("UPDATE artist SET name=:name WHERE id=:id");
    query.bindValue(":name",m_name);
    query.bindValue(":id",m_id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return;
    }
    else
    {
        QList<Track*> tracks = this->getTracks();
        for (int i = 0;i<tracks.count();i++)
        {
            tracks[i]->setArtistId(m_id);
            tracks[i]->update();
        }
    }
}

QList<Track*> Artist::getTracks()
{
    QList<Track*> tracks;
    qDebug() << "Artist IS " << m_id;
    if(m_id == 0)
    {
        qDebug() << "Artist not found";
        return tracks;
    }

    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT id FROM tracks WHERE artist_id = :id");
    query.bindValue(":id",m_id);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return tracks;
    }
    while (query.next())
    {
        int trackId = query.value(0).toInt();
        Track* track = Track::toId(trackId);
        tracks << track;
    }
    return tracks;
}


void Artist::remove()
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("DELETE FROM artist WHERE id=:id");
    query.bindValue(":id",this->m_id);

    bool ok = query.exec();

    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}
