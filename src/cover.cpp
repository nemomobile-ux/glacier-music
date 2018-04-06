#include "cover.h"
#include "musicbrainzconnect.h"


Cover::Cover(QObject *parent) : QObject(parent)
{
    m_coverDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/covers";;
}

void Cover::getCoverByTrackId(int trackId)
{
    m_track = Track::toId(trackId);
    if(!m_track)
    {
        return;
    }

    QString artist = m_track->getArtistName();
    QString title = m_track->getTitle();
    QString cover = m_track->getCover();

    if(cover.isEmpty())
    {
        MusicBrainzConnect *mbConnect = new MusicBrainzConnect();
        mbConnect->getData(artist,title);
        connect(mbConnect,SIGNAL(coverReady(QString)),this,SLOT(m_coverReady(QString)));
        connect(mbConnect,SIGNAL(downloadCover()),this,SIGNAL(coverLoaing()));
    }
    else
    {
        m_coverReady(cover);
    }
}

void Cover::m_coverReady(QString coverFile)
{
    m_track->setCover(m_coverDir+"/"+coverFile);
    emit coverReady(m_coverDir+"/"+coverFile);
}
