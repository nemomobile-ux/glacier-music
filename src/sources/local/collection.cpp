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

#include "collection.h"
#include "dbadapter.h"
#include "rescancollection.h"

#include <QDir>
#include <QStandardPaths>

#include <QDebug>

Collection::Collection(QObject* parent)
    : QObject(parent)
{
    m_rescanNotification = new Notification(this);
    m_rescanNotification->setAppName(QObject::tr("Music"));
    m_rescanNotification->setSummary(QObject::tr("Rescan collection"));
    m_rescanNotification->setBody(QObject::tr("Searching new music files"));
    m_rescanNotification->setAppIcon("/usr/share/glacier-music/images/icon-app-music.png");
    m_rescanNotification->setUrgency(Notification::Urgency::Low);

    m_firstRun = false;
    QDir cacheLocation = QDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    QFile dbFile(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/db.sql");

    if (!cacheLocation.exists() || !dbFile.exists()) {
        m_firstRun = true;
        cacheLocation.mkpath(cacheLocation.absolutePath() + "/images/");
    }

    dbAdapter* dba = new dbAdapter();
    connect(dba, &dbAdapter::baseCreate, this, &Collection::rescanCollection);
}

Collection::~Collection()
{
    m_rescanThread->quit();
}

void Collection::rescanCollection()
{
    RescanCollection* rCollection = new RescanCollection();

    m_rescanThread = new QThread;
    connect(m_rescanThread, &QThread::started, rCollection, &RescanCollection::scan);
    connect(rCollection, &RescanCollection::scanProcess, this, &Collection::m_rescanCollectionProgress);
    connect(rCollection, &RescanCollection::noMusicFiles, m_rescanNotification, &Notification::close);
    rCollection->moveToThread(m_rescanThread);
    m_rescanThread->start();
    m_rescanNotification->publish();
}

void Collection::m_rescanCollectionProgress(QVariant progress)
{
    emit updateRescanProgress(progress);
    m_rescanNotification->setProgress(progress);

    if (progress == 1) {
        m_rescanNotification->close();
        emit rescanCollectionFinished();
    }
}
