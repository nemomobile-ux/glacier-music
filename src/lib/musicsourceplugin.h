#ifndef MUSICSOURCEPLUGIN_H
#define MUSICSOURCEPLUGIN_H

#include <QObject>
#include "glaciermusic_global.h"

class GLACIERMUSIC_EXPORT MusicSourcePlugin : public QObject {
    Q_OBJECT

public:
    virtual bool enabled() = 0;

signals:
    void pluginChanged(QString id);
};

Q_DECLARE_INTERFACE(MusicSourcePlugin, "GlacierMusic.SourcePlugin")

#endif // MUSICSOURCEPLUGIN_H
