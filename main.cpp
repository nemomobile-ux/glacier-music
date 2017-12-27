/*
 * Copyright (C) 2017 Chupligin Sergey <neochapay@gmail.com>
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
#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif
#include <QtGui/QGuiApplication>


#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>
#include <QScreen>
#include <QCoreApplication>

#include <glacierapp.h>

#include "src/collection.h"
#include "src/cover.h"
#include "src/models/artistsqlmodel.h"
#include "src/models/tracksqlmodel.h"
#include "src/models/playlistmodel.h"

int main(int argc, char *argv[])
{
    setenv("QT_QUICK_CONTROLS_STYLE", "Nemo", 1);

    QGuiApplication *app = GlacierApp::app(argc, argv);
    app->setOrganizationName("NemoMobile");

    qmlRegisterType<Collection>("org.glacier.music.collection",1,0,"Collection");
    qmlRegisterType<Cover>("org.glacier.music.cover",1,0,"Cover");

    qmlRegisterType<ArtistSqlModel>("org.glacier.music.artistmodel",1,0,"ArtistModel");
    qmlRegisterType<TrackSqlModel>("org.glacier.music.trackmodel",1,0,"TrackModel");
    qmlRegisterType<PlayListModel>("org.glacier.music.playlistmodel",1,0,"PlaylistModel");

    QQuickWindow *window = GlacierApp::showWindow();
    window->setTitle(QObject::tr("Music"));
    window->setIcon(QIcon("/usr/share/glacier-music/images/icon-app-music.png"));

    return app->exec();
}
