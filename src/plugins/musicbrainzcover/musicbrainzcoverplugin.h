#ifndef MUSICBRAINZCOVERPLUGIN_H
#define MUSICBRAINZCOVERPLUGIN_H

#include <QVariant>
#include <coversourceplugin.h>

class MusicBrainzCoverPlugin : public MusicCoverPlugin {
    Q_OBJECT
    Q_INTERFACES(MusicCoverPlugin)
    Q_PLUGIN_METADATA(IID "GlacierMusic.CoverPlugin")

public:
    MusicBrainzCoverPlugin();
    bool enabled() { return true; }
    QString name() { return tr("MusicBrainz cover loader"); }

    QImage cover() { return m_coverImage; }
    void getCover(Track* track);

private:
    QImage m_coverImage = QImage("image://theme/music");
};

#endif // MUSICBRAINZCOVERPLUGIN_H
