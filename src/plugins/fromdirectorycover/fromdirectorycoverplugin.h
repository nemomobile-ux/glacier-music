#ifndef FROMDIRECTORYCOVERPLUGIN_H
#define FROMDIRECTORYCOVERPLUGIN_H

#include <QVariant>
#include <coversourceplugin.h>

class FromDirectoryCoverPlugin : public MusicCoverPlugin {
    Q_OBJECT
    Q_INTERFACES(MusicCoverPlugin)
    Q_PLUGIN_METADATA(IID "GlacierMusic.CoverPlugin")
public:
    FromDirectoryCoverPlugin();
    bool enabled() { return true; }
    QString name() { return tr("Load cover from directory"); }

    QImage cover() { return m_coverImage; }
    void getCover(Track* track);

private:
    QImage m_coverImage = QImage("image://theme/music");
};

#endif // FROMDIRECTORYCOVERPLUGIN_H
