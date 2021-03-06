#include "track.h"
#include "artist.h"
#include "dbadapter.h"
#include "audiofile.h"
#include "musicbrainzconnect.h"

Track::Track(const QString file)
{
    m_artist_id = 0;
    m_number = 0;
    m_year = 0;

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
            return;
        }

        Artist *newArtist = new Artist();
        newArtist->setName(trackFile->artist);
        if(newArtist->getId() == 0)
        {
            newArtist->insert();
        }

        m_artist = newArtist;
        m_artist_id = m_artist->idFromName(trackFile->artist);
        m_artist_title = trackFile->artist;
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
            int artist_id = query.value(1).toInt();
            QString title = query.value(2).toString();
            QString album = query.value(3).toString();
            QString comment = query.value(4).toString();
            QString genre = query.value(5).toString();

            int number = query.value(7).toInt();
            int year = query.value(8).toInt();

            if(artist_id != m_artist_id
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

int Track::insert()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    query.prepare("INSERT INTO tracks (`artist_id`, `filename`, `title`, `album`, `comment`, `genre`, `track`, `year`, `length`) \
                                 VALUES (:artistid, :filename, :title, :album, :comment, :genre, :track, :year, :length)");
    query.bindValue(":artistid",m_artist_id);
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
    query.bindValue(":AID",m_artist_id);
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
            audioFile.artist = m_artist->getName();
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

void Track::setArtistName(const QString name)
{
    Artist* artist = new Artist();
    int a_id = m_artist->idFromName(name);
    if(a_id == 0)
    {
        m_artist->setName(name);
        m_artist->insert();
        a_id = artist->idFromName(name);
    }
    m_artist_title = name;
    setArtistId(a_id);
}

void Track::setCover(const QString coverFile)
{
    if(coverFile != m_cover)
    {
        m_cover = coverFile;
        update();
    }
}

void Track::setArtistId(const int id)
{
    Artist* artist = new Artist();
    m_artist = artist->toId(id);
    m_artist_id = id;

    update();
}

void Track::remove()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("DELETE FROM tracks WHERE id=:id");
    query.bindValue(":id",id);

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

        if(m_artist->getTracks().length() == 0)
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
