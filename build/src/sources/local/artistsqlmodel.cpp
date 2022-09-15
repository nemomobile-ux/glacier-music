#include "artistsqlmodel.h"
#include <dbadapter.h>

#include <QSqlQueryModel>

ArtistSqlModel::ArtistSqlModel(QObject *parent) : QSqlQueryModel(parent)
{
    hash.insert(Qt::UserRole,QByteArray("artist_id"));
    hash.insert(Qt::UserRole+1,QByteArray("name"));
    refresh();
}

const char* ArtistSqlModel::SQL_SELECT = "SELECT id as artist_id, name FROM artist ORDER BY name ASC";

QVariant ArtistSqlModel::data(const QModelIndex &index, int role) const{
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

void ArtistSqlModel::searchQuery(const QString name)
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    setQuery(QString("SELECT id as artist_id, name FROM artist WHERE `name` LIKE '%%1%' ORDER BY name ASC").arg(name).toUtf8(), db);
}

void ArtistSqlModel::cleanQuery()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    setQuery("SELECT id as artist_id, name FROM artist ORDER BY name ASC", db);
}

void ArtistSqlModel::refresh()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    setQuery(SQL_SELECT, db);
}
