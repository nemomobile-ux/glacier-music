#ifndef COVERPLUGINMANAGER_H
#define COVERPLUGINMANAGER_H

#include "coversourceplugin.h"
#include "glaciermusic_global.h"

class GLACIERMUSIC_EXPORT CoverPluginManager : public QObject {
    Q_OBJECT
public:
    CoverPluginManager();
    QList<MusicCoverPlugin*> getPlugins() { return m_pluginList; }

signals:
    void pluginDataChanged(QString pluginId);

private:
    QList<MusicCoverPlugin*> m_pluginList;
};

#endif // COVERPLUGINMANAGER_H
