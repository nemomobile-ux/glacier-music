#include "musicbrainzcoverplugin.h"
#include "musicbrainzconnect.h"

MusicBrainzCoverPlugin::MusicBrainzCoverPlugin()
{
}

void MusicBrainzCoverPlugin::getCover(Track* track)
{
    qDebug() << Q_FUNC_INFO;
    /*Trying get cover from musicbrainz*/
    MusicBrainzConnect* mbConnect = new MusicBrainzConnect();
    mbConnect->getData(track->artist(), track->title());
    connect(mbConnect, &MusicBrainzConnect::coverReady, this, &MusicBrainzCoverPlugin::onCoverReady);
    connect(mbConnect, &MusicBrainzConnect::downloadCover, this, &MusicBrainzCoverPlugin::coverLoaing);
}

void MusicBrainzCoverPlugin::onCoverReady(QString coverFilePath)
{
    QImage cover(coverFilePath);
    if (!cover.isNull()) {
        emit coverChanged(cover);
    }
}
