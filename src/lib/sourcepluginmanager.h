#ifndef SOURCEPLUGINMANAGER_H
#define SOURCEPLUGINMANAGER_H

#include "glaciermusic_global.h"
#include "musicsourceplugin.h"
#include <QObject>

class GLACIERMUSIC_EXPORT SourcePluginManager : public QObject {
    Q_OBJECT
public:
    SourcePluginManager();
    QList<MusicSourcePlugin*> getPlugins() { return m_pluginList; }

signals:
    void pluginDataChanged(QString pluginId);

private:
    QList<MusicSourcePlugin*> m_pluginList;
};

#endif // SOURCEPLUGINMANAGER_H
