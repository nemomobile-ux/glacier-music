#ifndef MUSICBRAINZCOVERPLUGIN_H
#define MUSICBRAINZCOVERPLUGIN_H

#include <QVariant>
#include <coversourceplugin.h>

class MusicBrainzCoverPlugin : public CoverSourcePlugin {
    Q_OBJECT
    Q_INTERFACES(CoverSourcePlugin)
    Q_PLUGIN_METADATA(IID "GlacierMusic.CoverPlugin")

public:
    MusicBrainzCoverPlugin();
    bool enabled() { return true; }
    QString name() { return tr("MusicBrainz cover loader"); }

    QString cover();
    void getCover(QVariant data);
};

#endif // MUSICBRAINZCOVERPLUGIN_H
