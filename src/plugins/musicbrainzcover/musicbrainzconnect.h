/*
 * Copyright (C) 2022 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef MUSICBRAINZCONNECT_H
#define MUSICBRAINZCONNECT_H

#include <QFile>
#include <QMap>
#include <QObject>

class MusicBrainzConnect : public QObject {
    Q_OBJECT
public:
    explicit MusicBrainzConnect(QObject* parent = 0);

signals:
    void answerNotCorrect();
    void downloadCover();
    void coverReady(QString fileName);
    void downloadCoverProgress(float process);

public slots:
    void getData(const QString artist, const QString title);
    void loadCover(QString releaseId);

private slots:
    void dataReady(QByteArray answer);
    void coverNetworkData(QByteArray answer);
    void onFinishedDownloadCover(QByteArray answer);

private:
    QString m_covers_dir;
    QMap<QString, QString> m_song;
    QFile* m_coverFile;

    bool m_redirect;

    void downloadCoverImage(QString coverURL);
};

#endif // MUSICBRAINZCONNECT_H
