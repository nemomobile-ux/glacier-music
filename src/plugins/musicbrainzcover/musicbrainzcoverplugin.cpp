#include "musicbrainzcoverplugin.h"
#include "musicbrainzconnect.h"

MusicBrainzCoverPlugin::MusicBrainzCoverPlugin()
    : m_track(nullptr)
{
}

void MusicBrainzCoverPlugin::getCover(Track* track)
{
    if (track == m_track || track == nullptr) {
        return;
    }

    if (track->artist().isEmpty() || track->title().isEmpty()) {
        return;
    }

    m_track = track;

    /*Trying get cover from musicbrainz*/
    MusicBrainzConnect* mbConnect = new MusicBrainzConnect();
    mbConnect->getData(track->artist(), track->title());
    connect(mbConnect, &MusicBrainzConnect::coverReady, this, &MusicBrainzCoverPlugin::onCoverReady);
    connect(mbConnect, &MusicBrainzConnect::downloadCover, this, &MusicBrainzCoverPlugin::coverLoaing);
}

void MusicBrainzCoverPlugin::onCoverReady(QString coverFilePath)
{
    QImage cover(coverFilePath);
    if (!cover.isNull() && m_track != nullptr) {
        m_track->setCover(cover);
    }
}
