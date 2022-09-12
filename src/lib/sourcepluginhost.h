#ifndef SOURCEPLUGINHOST_H
#define SOURCEPLUGINHOST_H

#include <QObject>
#include <QPluginLoader>

#include "glaciermusic_global.h"
#include "musicsourceplugin.h"

class QPluginLoader;

class GLACIERMUSIC_EXPORT SourcePluginHost : public QObject
{
public:
    SourcePluginHost(const QString& fileName, QObject *parent = 0);

    bool load();
    MusicSourcePlugin *get();

    bool enabled();
    bool valid() {return m_valid;}

private:
    QPluginLoader* m_loader;
    MusicSourcePlugin* m_plugin;
    QString m_fileName;

    bool m_valid;
};

#endif // SOURCEPLUGINHOST_H
