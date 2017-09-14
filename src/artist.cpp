#include "artist.h"
#include "track.h"
#include "dbadapter.h"

Artist::Artist(QObject *parent) : Item(parent)
{

}

QHash<int, Artist*> Artist::m_cache;

Artist* Artist::toId(int artistId)
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
    }
    if(query.next())
    {
        Artist* artist = new Artist();
        artist->id = artistId;
        artist->m_name = query.value(0).toString();
        m_cache.insert(artistId,artist);
        return artist;
    }
    m_cache.insert(artistId,0);
    return 0;
}

int Artist::idFromName(QString name)
{
    int id = 0;
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    //QString str = QString("SELECT id FROM artist WHERE `name`='%1'").arg(name);

    query.prepare("SELECT id FROM artist WHERE name=:name");
    query.bindValue(":name",name);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return -1;
    }

    if(query.next())
    {
        id = query.value(0).toInt();
    }

    return id;
}

int Artist::insert()
{
    if(m_name.length() == 0)
    {
        return 0;
    }

    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    QString str = QString("INSERT INTO artist (name) VALUES ('%1')").arg(m_name);

    bool ok = query.exec(str);
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return -1;
    }

    return query.lastInsertId().toInt();
}

bool Artist::setName(QString name)
{
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    QString str = QString("SELECT id FROM artist WHERE `name`='%1'").arg(name);

    bool ok = query.exec(str);
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
        return false;
    }

    if(query.next())
    {
        id = query.value(0).toInt();
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
    query.bindValue(":id",id);

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
            tracks[i]->setArtistId(id);
            tracks[i]->update();
        }
    }
}

QList<Track*> Artist::getTracks()
{
    QList<Track*> tracks;
    QSqlDatabase db = dbAdapter::instance().db;
    QSqlQuery query(db);
    query.prepare("SELECT id FROM tracks WHERE artist_id = :id");
    query.bindValue(":id",id);

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
    query.bindValue(":id",this->id);

    bool ok = query.exec();

    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}
