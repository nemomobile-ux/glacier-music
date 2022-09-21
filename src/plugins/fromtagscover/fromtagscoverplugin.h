#ifndef FROMTAGSCOVERPLUGIN_H
#define FROMTAGSCOVERPLUGIN_H

#include <QVariant>
#include <coversourceplugin.h>

class FromTagsCoverPlugin : public MusicCoverPlugin {
    Q_OBJECT
    Q_INTERFACES(MusicCoverPlugin)
    Q_PLUGIN_METADATA(IID "GlacierMusic.CoverPlugin")
public:
    FromTagsCoverPlugin();
    bool enabled() { return true; }
    QString name() { return tr("Load cover from tags"); }

    QImage cover() { return m_coverImage; }
    void getCover(Track* track);

private:
    QImage m_coverImage = QImage("image://theme/music");
};

#endif // FROMTAGSCOVERPLUGIN_H
