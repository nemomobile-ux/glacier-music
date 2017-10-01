#ifndef MUSICBRAINZCONNECT_H
#define MUSICBRAINZCONNECT_H

#include <QFile>
#include <QNetworkReply>
#include <QObject>

class MusicBrainzConnect : public QObject
{
    Q_OBJECT
public:
    explicit MusicBrainzConnect(QObject *parent = 0);

signals:
    void answerNotCorrect();
    void downloadCover();
    void coverReady();
    void downloadCoverProgress(float process);

public slots:
    void getData(const QString artist,const QString title);
    void loadCover(QString releaseId);

private slots:
    void dataReady();
    void coverNetworkData(QNetworkReply *reply);
    void onFinishedDownloadCover(QNetworkReply *reply);
    void onDownloadCoverProgress(qint64 bytesRead,qint64 bytesTotal);
    void onReadyCoverRead();
    void onReplyCoverFinished();

private:
    QString m_covers_dir;

    QNetworkReply *m_response;
    QNetworkReply *m_iresponse;
    QNetworkReply *m_cresponse;

    QNetworkAccessManager *m_manager;
    QNetworkAccessManager *m_imanager;
    QNetworkAccessManager *m_cmanager;

    QMap<QString,QString> m_song;

    QFile *m_coverFile;

    void downloadCoverImage(QString coverURL);
};

#endif // MUSICBRAINZCONNECT_H
