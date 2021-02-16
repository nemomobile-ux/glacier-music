#ifndef PEAKSCREATOR_H
#define PEAKSCREATOR_H

#include <QObject>
#include <QtQuick>
#include <QtQml>
#include <QAudioDecoder>

class PeaksCreator : public QObject
{
    Q_OBJECT
public:
    explicit PeaksCreator(QObject *parent = 0);
    void setFileName(QString path);
    void getPeaks();

signals:
    void peaksReady(QVector<double>);

private slots:
    void mSetBuffer();

private:
    void loadAudioFile();
    void mFormatPeaks();
    void mLoadPeaksFromFile();
    void mSavePeaksToFile();

    qreal mGetPeakValue(const QAudioFormat &format);

    QAudioDecoder *m_decoder;
    QAudioBuffer m_buffer;
    QVector<double> m_samples;

    QByteArray m_audioData;
    qint64 m_duration = 0;

    QString m_peaksDir;
    QString m_peaksFile;
    QString m_fileName;
};

#endif // PEAKSCREATOR_H
