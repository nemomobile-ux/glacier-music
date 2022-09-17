#include "sourcepluginhost.h"

SourcePluginHost::SourcePluginHost(const QString& fileName, QObject* parent)
{
    QPluginLoader pluginLoader(fileName);
    QObject* plugin = pluginLoader.instance();
    if (plugin) {
        m_plugin = qobject_cast<MusicSourcePlugin*>(plugin);
        if (m_plugin == nullptr) {
            qWarning("Can't cast plugin");
            pluginLoader.unload();
        } else {
            m_valid = true;
        }
    } else {
        qDebug() << "Plugin not found" << fileName << pluginLoader.errorString();
    }
}

MusicSourcePlugin* SourcePluginHost::get()
{
    if (!m_plugin) {
        return nullptr;
    }
    return m_plugin;
}

bool SourcePluginHost::enabled()
{
    if (!m_plugin) {
        return false;
    }
    return m_plugin->enabled();
}
