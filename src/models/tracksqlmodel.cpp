#include "tracksqlmodel.h"
#include "../dbadapter.h"

#include <QDebug>

TrackSqlModel::TrackSqlModel(QObject *parent) : QSqlQueryModel(parent)
{
    hash.insert(Qt::UserRole  ,QByteArray("track_id"));
    hash.insert(Qt::UserRole+1,QByteArray("artist_id"));
    hash.insert(Qt::UserRole+2,QByteArray("title"));
    hash.insert(Qt::UserRole+3,QByteArray("album"));
    hash.insert(Qt::UserRole+4,QByteArray("comment"));
    hash.insert(Qt::UserRole+5,QByteArray("genre"));
    hash.insert(Qt::UserRole+6,QByteArray("track"));
    hash.insert(Qt::UserRole+7,QByteArray("year"));
    hash.insert(Qt::UserRole+8,QByteArray("filename"));
    hash.insert(Qt::UserRole+9,QByteArray("artist_name"));
    refresh();
}

const char* TrackSqlModel::SQL_SELECT = "SELECT tracks.id as track_id, \
                                        tracks.artist_id, \
                                        tracks.title, \
                                        tracks.album, \
                                        tracks.comment, \
                                        tracks.genre, \
                                        tracks.track, \
                                        tracks.year, \
                                        tracks.filename, \
                                        artist.name as artist_name \
                                        FROM tracks \
                                        INNER JOIN artist ON artist.id = tracks.artist_id \
                                        ORDER BY artist_name ASC";

QVariant TrackSqlModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

void TrackSqlModel::refresh()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    setQuery(SQL_SELECT, db);
}


void TrackSqlModel::setArtist(const int artist_id)
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    setQuery(QString("SELECT * \
                        FROM tracks \
                        WHERE artist_id = %1 ORDER BY title ASC").arg(artist_id).toUtf8(), db);
}

void TrackSqlModel::cleanQuery()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    this->setQuery("SELECT tracks.id as track_id, \
                               tracks.artist_id, \
                               tracks.title, \
                               tracks.album, \
                               tracks.comment, \
                               tracks.genre, \
                               tracks.track, \
                               tracks.year, \
                               tracks.filename, \
                               artist.name as artist_name \
                               FROM tracks \
                               INNER JOIN artist ON artist.id = tracks.artist_id \
                        ORDER BY artist_name ASC", db);
}
