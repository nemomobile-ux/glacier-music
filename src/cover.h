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

#ifndef COVER_H
#define COVER_H

#include "track.h"
#include <QObject>

class Cover : public QObject {
    Q_OBJECT
public:
    explicit Cover(QObject* parent = 0);

signals:
    void coverReady(QString coverFile);
    void coverLoaing();

public slots:
    void getCoverByTrack(const QString artist,
        const QString title,
        const QString album);

private slots:
    void m_coverReady(QString coverFile);

private:
    QString m_coverDir;
    Track* m_track;
};

#endif // COVER_H
