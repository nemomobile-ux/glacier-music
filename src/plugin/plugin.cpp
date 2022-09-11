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

#include <QtQml>
#include <QtGlobal>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>

#include "blurredimage.h"
#include "wavewidget.h"
#include "artistsqlmodel.h"
#include "tracksqlmodel.h"
#include "playlistmodel.h"

class Q_DECL_EXPORT GlacierMusicPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.glacier.music")
public:
    virtual ~GlacierMusicPlugin() { }

    void initializeEngine(QQmlEngine *, const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("org.glacier.music"));
        qmlRegisterModule(uri, 1, 0);
    }

    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("org.glacier.music"));
        // @uri org.glacier.music
        qmlRegisterType<WaveWidget>(uri ,1,0,"WaveWidget");
        qmlRegisterType<BlurredImage>(uri,1,0,"BlurredImage");

        qmlRegisterType<ArtistSqlModel>(uri,1,0,"ArtistModel");
        qmlRegisterType<TrackSqlModel>(uri,1,0,"TrackModel");
        qmlRegisterType<PlayListModel>(uri,1,0,"PlaylistModel");
    }
};

#include "plugin.moc"
