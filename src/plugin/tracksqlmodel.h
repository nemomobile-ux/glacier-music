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
#ifndef TRACKSQLMODEL_H
#define TRACKSQLMODEL_H

#include <QSqlQueryModel>

class TrackSqlModel :public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit TrackSqlModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {return hash;}

private:
    const static char* SQL_SELECT;
    QHash<int,QByteArray> hash;

public slots:
    void refresh();
    void setArtist(const int artist_id);
    void cleanQuery();
};

#endif // TRACKSQLMODEL_H
