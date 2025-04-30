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

#include "rescancollection.h"
#include "dbadapter.h"
#include "track.h"

RescanCollection::RescanCollection(QObject* parent)
    : QObject(parent)
{
}

void RescanCollection::scan()
{
    qDebug() << "Start rescan collection";
    /*in first - check removed files in db*/
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    query.prepare("SELECT id, filename FROM tracks");
    bool ok = query.exec();
    if (!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }

    QStringList filesInDb;

    /*Check on removed files*/
    while (query.next()) {
        QString fileName = query.value(1).toString();
        QFile tFile(fileName);
        if (!tFile.exists()) {
            qDebug() << "!!! File not found " << fileName;
            QSqlQuery rquery(db);
            rquery.exec("DELETE FROM tracks WHERE filename='" + fileName + "'");
        } else {
            filesInDb << fileName;
        }
    }

    /*in second - check new files not in db*/
    // Yes i know about flac, cue and etc...i add it later. Or you can create pr
    QStringList allowedExtensions;
    allowedExtensions << "*.mp3"
                      << "*.ogg";

    QStringList scanDir = aviableDirs();
    QStringList newFiles;

    for (int i = 0; i < scanDir.count(); i++) {
        qDebug() << "Scanning " << scanDir[i];

        QDirIterator it(scanDir[i], allowedExtensions, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QString file = it.next();
            if (!filesInDb.contains(file)) {
                newFiles << file;
            }
        }
    }

    double m_aviableFiles = newFiles.count();
    double m_scannedFiles = 0;

    if (m_aviableFiles == 0 && filesInDb.count() == 0) {
        emit noMusicFiles();
    } else {
        foreach (const QString& fileUrl, newFiles) {
            Track* track = new Track(fileUrl);
            Q_UNUSED(track);
            m_scannedFiles++;
            delete (track);

            double prc = m_scannedFiles / m_aviableFiles;
            emit scanProcess(QVariant(prc));
        }
        emit scanProcess(1);
    }
    emit scanFinished();
}

QStringList RescanCollection::aviableDirs()
{
    QStringList aviableDirs;
    // Add download dir
    aviableDirs << QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first();

    qDebug() << "DOWNLOAD" << QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first();

    // Add standart music path
    if (QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first() != QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first() && QDir(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first()).exists()) {
        aviableDirs << QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first();
    }

    qDebug() << "MUSIC!!!" << QStandardPaths::standardLocations(QStandardPaths::MusicLocation);

    // Find sdcard
    // @todo need add removiable media not hardcoded
    QDir mountDir("/media/sdcard/");
    mountDir.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    for (int i = 0; i < mountDir.entryList().count(); i++) {
        aviableDirs << mountDir.absolutePath() + "/" + mountDir.entryList().at(i);
        qDebug() << aviableDirs.last();
    }
    return aviableDirs;
}
