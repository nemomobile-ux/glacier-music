#include "cover.h"
#include "audiofile.h"
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

    QFile coverFile(cover);

    if(cover.isEmpty() || !coverFile.exists())
    {
        /*Search cover to tags*/
        AudioFile file(m_track->getFileName());
        QImage coverImgFromTags = file.coverImg();
        if(!coverImgFromTags.isNull()) {
            QString coverPath = m_coverDir+"/"+artist+"_"+title+".jpg";
            coverImgFromTags.save(coverPath,"jpg",100);
            qDebug() << "We have cover in tag. Save to " << coverPath ;
            m_coverReady(coverPath);
            return;
        }

        /*Search cover image in file folder*/
        QFileInfo musicFileInfo(m_track->getFileName());
        QString musicFileDir = musicFileInfo.absoluteDir().absolutePath();
        QFile localCover(musicFileDir+"/cover.jpg");
        if(localCover.exists())
        {
            m_coverReady(musicFileDir+"/cover.jpg");
            return;
        }

        /*Trying get cover from musicbrainz*/
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
    m_track->setCover(coverFile);
    emit coverReady(coverFile);
}
