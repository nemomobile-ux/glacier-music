#include "sourcepluginmanager.h"
#include "sourcepluginhost.h"

#include <QDir>

SourcePluginManager::SourcePluginManager()
{
    QDir pluginsDir("/usr/lib/glacier-music/plugin/sources");
    for (const QString& file : pluginsDir.entryList(QDir::Files)) {
        SourcePluginHost* sph = new SourcePluginHost(pluginsDir.absoluteFilePath(file), this);
        if (sph) {
            if (sph->valid()) {
                m_pluginList.push_back(sph->get());
                connect(sph->get(), &MusicSourcePlugin::pluginChanged, this, &SourcePluginManager::pluginDataChanged);
            } else {
                qDebug() << "Loading" << pluginsDir.absoluteFilePath(file) << " fail";
            }
        } else {
            qWarning() << "can't load" << pluginsDir.absoluteFilePath(file);
        }
        delete (sph);
    }
}

SourcePluginManager::~SourcePluginManager()
{
}
