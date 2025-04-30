/*
 * Copyright (C) 2022-2025 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef DBADAPTER_H
#define DBADAPTER_H

#include <QObject>
#include <QSqlQueryModel>
#include <QtSql>

class dbAdapter : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isValid READ isValid NOTIFY isValidChanged FINAL)

public:
    explicit dbAdapter(QObject* parent = 0);
    ~dbAdapter();

    static dbAdapter& instance();
    QSqlQueryModel* getTable(QString table);
    QSqlDatabase getDatabase() { return m_db; }

    bool isValid() const;

signals:
    void baseCreate();

    void isValidChanged();

public slots:

private:
    QSqlDatabase _getDatabase();
    QSqlQuery query;
    QMutex lock;
    void initDB(QSqlDatabase db);
    QSqlDatabase m_db;
    bool m_isValid;
};

#endif // DBADAPTER_H
