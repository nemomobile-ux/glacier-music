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


#include "coverpluginmanager.h"

#include <QDir>
#include <QPluginLoader>

CoverPluginManager::CoverPluginManager()
{
    QDir pluginsDir("/usr/lib/glacier-music/plugin/cover");
    for (const QString& file : pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader("/usr/lib/glacier-music/plugin/cover/" + file);
        QObject* plugin = pluginLoader.instance();
        if (plugin) {
            MusicCoverPlugin* sourcePlugin = qobject_cast<MusicCoverPlugin*>(plugin);
            if (sourcePlugin != nullptr) {
                m_pluginList.push_back(sourcePlugin);
            }
        }
    }
}
