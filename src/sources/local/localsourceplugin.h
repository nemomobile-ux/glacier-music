#ifndef LOCALSOURCEPLUGIN_H
#define LOCALSOURCEPLUGIN_H

#include <musicsourceplugin.h>

class LocalSourcePlugin: public MusicSourcePlugin
{
    Q_OBJECT
    Q_INTERFACES(MusicSourcePlugin)
    Q_PLUGIN_METADATA( IID "GlacierMusic.SourcePlugin")
public:
    LocalSourcePlugin(QObject *parent = nullptr);
    bool enabled() {return true;}
    QString name() {return tr("Local music database");}
};

#endif // LOCALSOURCEPLUGIN_H
