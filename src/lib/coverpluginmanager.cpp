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
