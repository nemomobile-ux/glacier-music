#include "musicbrainzconnect.h"
#include "downloader.h"

#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

MusicBrainzConnect::MusicBrainzConnect(QObject *parent) : QObject(parent)
{
    m_covers_dir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/covers";
    QDir covers(m_covers_dir);
    if(!covers.exists())
    {
        covers.mkpath(m_covers_dir);
    }
}

void MusicBrainzConnect::getData(const QString artist, const QString title)
{
    if(title.length() > 0 && artist.length() > 0)
    {
        Downloader *mbDownloader = new Downloader("https://musicbrainz.org/ws/2/recording?query="+title+"%20artist:"+artist+"&fmt=json");
        connect(mbDownloader,SIGNAL(stringReady(QByteArray)),this,SLOT(dataReady(QByteArray)));
        mbDownloader->loadData();
    }
}

void MusicBrainzConnect::dataReady(QByteArray answer)
{
    QJsonDocument data_doc = QJsonDocument::fromJson(answer);
    QJsonObject data_obj = data_doc.object();
    QJsonArray recordingsArray = data_obj["recordings"].toArray();

    if(recordingsArray.count() == 0)
    {
        answerNotCorrect();
        return;
    }

    QJsonObject songObject = recordingsArray.first().toObject();
    m_song.insert("title",songObject["title"].toString());
    m_song.insert("id",songObject["id"].toString());

    //TODO: Add artist info parse
    /*QJsonArray f_artistObject = songObject["artist-credit"].toArray();
    QJsonArray artistObject = f_artistObject[0].toArray();
    qDebug() << "----------";
    qDebug() << artistObject["artist"].toString();*/

    /*Load album data*/
    QJsonArray f_releases = songObject["releases"].toArray();
    QJsonObject releases = f_releases.first().toObject();

    m_song.insert("release_id",releases["id"].toString());
    m_song.insert("release_title",releases["title"].toString());

    QFile cover(m_covers_dir+"/"+m_song.value("release_id")+".jpg");
    if(!cover.exists())
    {
        emit downloadCover();
        loadCover(m_song.value("release_id"));
    }
    else
    {
        emit coverReady(m_covers_dir+"/"+m_song.value("release_id")+".jpg");
    }
}

void MusicBrainzConnect::loadCover(QString releaseId)
{
    if(releaseId.length() == 0)
    {
        return;
    }

    qDebug() << "Load cover form "<< QString("https://coverartarchive.org/release/"+releaseId);

    Downloader *cbDownloader = new Downloader("https://coverartarchive.org/release/"+releaseId);
    connect(cbDownloader,SIGNAL(stringReady(QByteArray)),this,SLOT(coverNetworkData(QByteArray)));
    cbDownloader->loadData();
}


void MusicBrainzConnect::coverNetworkData(QByteArray answer)
{
    QJsonDocument cover_doc = QJsonDocument::fromJson(answer);
    QJsonObject cover_obj = cover_doc.object();
    QJsonArray coversArray = cover_obj["images"].toArray();
    QJsonObject cover = coversArray.first().toObject();

    if(!cover["image"].toString().isEmpty())
    {
        downloadCoverImage(cover["image"].toString());
    }
}

void MusicBrainzConnect::downloadCoverImage(QString coverURL)
{
    qDebug() << "Start download " << coverURL;
    QString saveFilePath = m_covers_dir+"/"+m_song.value("release_id")+".jpg";

    Downloader *imageDownloader = new Downloader(coverURL);
    connect(imageDownloader,SIGNAL(stringReady(QByteArray)),this,SLOT(onFinishedDownloadCover(QByteArray)));
    connect(imageDownloader,SIGNAL(downloadProgress(float)),this,SIGNAL(downloadCoverProgress(float)));
    imageDownloader->loadData();

    m_coverFile = new QFile;
    m_coverFile->setFileName(saveFilePath);
    m_coverFile->open(QIODevice::WriteOnly);
}



void MusicBrainzConnect::onFinishedDownloadCover(QByteArray answer)
{
    if(answer.size() > 0) {
        m_coverFile->write(answer);
        m_coverFile->close();
        m_coverFile->deleteLater();
        emit coverReady(m_covers_dir+"/"+m_song.value("release_id")+".jpg");
    } else {
        qDebug() << Q_FUNC_INFO << "Got empty answer";
    }

}
