#include "sourcepluginmanager.h"

#include <QDir>
#include <QPluginLoader>

SourcePluginManager::SourcePluginManager()
{
    QDir pluginsDir("/usr/lib/glacier-music/plugin/sources");
    for (const QString& file : pluginsDir.entryList(QDir::Files)) {
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
