#ifndef LOCALSOURCEPLUGIN_H
#define LOCALSOURCEPLUGIN_H

#include "tracksmodel.h"

#include <musicsourceplugin.h>

class LocalSourcePlugin : public MusicSourcePlugin {
    Q_OBJECT
    Q_INTERFACES(MusicSourcePlugin)
    Q_PLUGIN_METADATA(IID "GlacierMusic.SourcePlugin")
public:
    LocalSourcePlugin(QObject* parent = nullptr);
    bool enabled() { return true; }
    QString name() { return tr("Local music database"); }

    bool hasBack();
    void setHasBack(bool hasBack);

    bool hasForward();
    void setHasForward(bool hasForward);

    TracksModel* tracksModel();

private slots:
    void calcButtonStatus();
    void loadPlaylistFromDB();

private:
    TracksModel* m_tracksModel;

    bool m_hasBack;
    bool m_hasForward;
};

#endif // LOCALSOURCEPLUGIN_H
