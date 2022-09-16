#ifndef MUSICBRAINZCONNECT_H
#define MUSICBRAINZCONNECT_H

#include <QFile>
#include <QMap>
#include <QObject>

class MusicBrainzConnect : public QObject {
    Q_OBJECT
public:
    explicit MusicBrainzConnect(QObject* parent = 0);

signals:
    void answerNotCorrect();
    void downloadCover();
    void coverReady(QString fileName);
    void downloadCoverProgress(float process);

public slots:
    void getData(const QString artist, const QString title);
    void loadCover(QString releaseId);

private slots:
    void dataReady(QByteArray answer);
    void coverNetworkData(QByteArray answer);
    void onFinishedDownloadCover(QByteArray answer);

private:
    QString m_covers_dir;
    QMap<QString, QString> m_song;
    QFile* m_coverFile;

    bool m_redirect;

    void downloadCoverImage(QString coverURL);
};

#endif // MUSICBRAINZCONNECT_H
