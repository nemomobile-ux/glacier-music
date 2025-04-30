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

#include "sourcepluginmanager.h"

#include <QDir>
#include <QPluginLoader>

SourcePluginManager::SourcePluginManager()
{
    QDir pluginsDir("/usr/lib/glacier-music/plugin/sources");
    QList<QString> pluginsLibList = pluginsDir.entryList(QDir::Files);

    for (const QString& file : std::as_const(pluginsLibList)) {
        QPluginLoader pluginLoader("/usr/lib/glacier-music/plugin/sources/" + file);
        QObject* plugin = pluginLoader.instance();
        if (plugin) {
            MusicSourcePlugin* sourcePlugin = qobject_cast<MusicSourcePlugin*>(plugin);
            if (sourcePlugin != nullptr) {
                m_pluginList.push_back(sourcePlugin);
                connect(sourcePlugin, &MusicSourcePlugin::pluginChanged, this, &SourcePluginManager::pluginDataChanged);
            }
        }
    }
}

MusicSourcePlugin* SourcePluginManager::getPluginById(const QString id)
{
    if (m_pluginList.empty()) {
        return nullptr;
    }

    for (MusicSourcePlugin* plugin : std::as_const(m_pluginList)) {
        if (plugin->id() == id) {
            return plugin;
        }
    }

    return nullptr;
}
