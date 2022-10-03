#ifndef MUSICSOURCEPLUGIN_H
#define MUSICSOURCEPLUGIN_H

#include "glaciermusic_global.h"
#include "tracksmodel.h"

#include <QAbstractListModel>
#include <QObject>

class GLACIERMUSIC_EXPORT MusicSourcePlugin : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool hasBack READ hasBack WRITE setHasBack NOTIFY hasBackChanged)
    Q_PROPERTY(bool hasForward READ hasForward WRITE setHasForward NOTIFY hasForwardChanged)

public:
    enum PlayMode {
        Random,
        Artist,
        ArtistShuffle,
        Album,
        AlbumShuffle,
        Directory,
        DirectoryShuffle,
        Smart
    };
    Q_ENUMS(PlayMode)

    virtual bool enabled() = 0;
    virtual QString name() = 0;

    virtual bool hasBack() = 0;
    virtual void setHasBack(bool hasBack) = 0;

    virtual bool hasForward() = 0;
    virtual void setHasForward(bool hasForward) = 0;

    virtual TracksModel* tracksModel() = 0;
    virtual void loadPlaylist(PlayMode mode, QString param = "") = 0;
    virtual void clearPlaylist() = 0;

signals:
    void
    pluginChanged(QString id);

    void hasBackChanged();
    void hasForwardChanged();
};

Q_DECLARE_INTERFACE(MusicSourcePlugin, "GlacierMusic.SourcePlugin")

#endif // MUSICSOURCEPLUGIN_H
