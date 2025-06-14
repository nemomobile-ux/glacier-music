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

#ifndef COLLECTION_H
#define COLLECTION_H

#include <QDir>
#include <QObject>

#include <notification.h>

class Collection : public QObject {
    Q_OBJECT
public:
    explicit Collection(QObject* parent = 0);
    Q_INVOKABLE bool isFirstRun() { return m_firstRun; }
    ~Collection();

signals:
    void newFile(QString path);
    void updateRescanProgress(QVariant prc);
    void rescanCollectionFinished();

public slots:
    void rescanCollection();

private slots:
    void m_rescanCollectionProgress(QVariant progress);

private:
    bool m_firstRun;
    QStringList aviableDirs();
    Notification* m_rescanNotification;
};

#endif // COLLECTION_H
