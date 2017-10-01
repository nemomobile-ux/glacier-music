#include "musicbrainzconnect.h"
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QStandardPaths>

MusicBrainzConnect::MusicBrainzConnect(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager();
    m_imanager = new QNetworkAccessManager();
    m_cmanager = new QNetworkAccessManager();
    m_covers_dir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/covers";
    QDir covers(m_covers_dir);
    if(!covers.exists())
    {
        covers.mkpath(m_covers_dir);
    }
}

void MusicBrainzConnect::getData(const QString artist, const QString title)
{
    QUrl url("https://musicbrainz.org/ws/2/recording?query="+title+"%20artist:"+artist+"&fmt=json");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("User-Agent","Glacier music player");
    m_response = m_manager->get(request);

    connect(m_response,SIGNAL(finished()),this,SLOT(dataReady()));
}

void MusicBrainzConnect::dataReady()
{
    QString answer = m_response->readAll();
    QJsonDocument data_doc = QJsonDocument::fromJson(answer.toUtf8());
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
        emit coverReady(m_song.value("release_id")+".jpg");
    }
}

void MusicBrainzConnect::loadCover(QString releaseId)
{
    qDebug() << "Load cover form "<< QString("http://archive.org/download/mbid-"+releaseId+"/index.json");

    QUrl url(QString("http://coverartarchive.org/release/"+releaseId));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("User-Agent","Glacier music player");
    m_iresponse = m_imanager->get(request);

    connect(m_imanager,SIGNAL(finished(QNetworkReply*)),this, SLOT(coverNetworkData(QNetworkReply*)));
}


void MusicBrainzConnect::coverNetworkData(QNetworkReply * reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
    }

    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 307 || reply->rawHeaderList().contains("Location"))
    {
        QNetworkRequest req(reply->header(QNetworkRequest::LocationHeader).toString());
        m_imanager->get(req);
        return;
    }

    QString answer = reply->readAll();

    QJsonDocument cover_doc = QJsonDocument::fromJson(answer.toUtf8());
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

    QNetworkRequest request;
    request.setUrl(QUrl(coverURL));
    m_cresponse = m_cmanager->get(request);

    m_coverFile = new QFile;
    m_coverFile->setFileName(saveFilePath);
    m_coverFile->open(QIODevice::WriteOnly);

    connect(m_cresponse,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(onDownloadCoverProgress(qint64,qint64)));
    connect(m_cmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinishedDownloadCover(QNetworkReply*)));
}


void MusicBrainzConnect::onDownloadCoverProgress(qint64 bytesRead,qint64 bytesTotal)
{
    float progress;
    progress = bytesRead/bytesTotal*100;
    emit downloadCoverProgress(progress);
}


void MusicBrainzConnect::onFinishedDownloadCover(QNetworkReply * reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
    }

    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 307 || reply->rawHeaderList().contains("Location"))
    {
        QNetworkRequest req(reply->header(QNetworkRequest::LocationHeader).toString());
        qDebug() << "Redirect: " << reply->header(QNetworkRequest::LocationHeader).toString();
        m_cmanager->get(req);
        return;
    }

    m_coverFile->write(reply->readAll());
    m_coverFile->close();
    m_coverFile->deleteLater();
    emit coverReady(m_song.value("release_id")+".jpg");
}
