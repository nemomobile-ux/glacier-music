#ifndef COVERSOURCEPLUGIN_H
#define COVERSOURCEPLUGIN_H

#include "glaciermusic_global.h"
#include "track.h"
#include <QImage>
#include <QObject>

class GLACIERMUSIC_EXPORT MusicCoverPlugin : public QObject {
    Q_OBJECT
    Q_PROPERTY(QImage cover READ cover NOTIFY coverChanged)

public:
    virtual bool enabled() = 0;
    virtual QString name() = 0;

    virtual QImage cover() = 0;
    virtual void getCover(Track* track) = 0;

signals:
    void coverChanged();
};

Q_DECLARE_INTERFACE(MusicCoverPlugin, "GlacierMusic.CoverPlugin")
#endif // COVERSOURCEPLUGIN_H
