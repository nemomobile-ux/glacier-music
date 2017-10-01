#include "cover.h"
#include "track.h"
#include "musicbrainzconnect.h"


Cover::Cover(QObject *parent) : QObject(parent)
{
    m_coverDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/covers";;
}

void Cover::getCoverByTrackId(int trackId)
{
    Track *track = Track::toId(trackId);
    if(!track)
    {
        return;
    }

    QString artist = track->getArtistName();
    QString title = track->getTitle();
    QString cover = track->getCover();

    if(cover.isEmpty())
    {
        MusicBrainzConnect *mbConnect = new MusicBrainzConnect();
        mbConnect->getData(artist,title);
        connect(mbConnect,SIGNAL(coverReady(QString)),this,SLOT(m_coverReady(QString)));
    }
    else
    {
        m_coverReady(cover);
    }
}

void Cover::m_coverReady(QString coverFile)
{
    emit coverReady(m_coverDir+"/"+coverFile);
}
