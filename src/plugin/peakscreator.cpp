#include "peakscreator.h"

#include <QDir>
#include <QStandardPaths>

//NEED TO FIX
static const int INTERVAL = 60;

PeaksCreator::PeaksCreator(QObject *parent)
    : QObject(parent)
    , m_decoder(new QAudioDecoder(this))
{
    connect(m_decoder, &QAudioDecoder::bufferReady,
            this, &PeaksCreator::mSetBuffer);

    connect(m_decoder, &QAudioDecoder::finished,
            this, &PeaksCreator::mSavePeaksToFile);

    m_peaksDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/peaks";
    QDir peaks(m_peaksDir);
    if(!peaks.exists()) {
        peaks.mkpath(m_peaksDir);
    }
}

void PeaksCreator::setFileName(QString path)
{
    if(path == m_fileName) {
        return;
    }

    QFile audioFile(path);
    if(!audioFile.exists()) {
        return;
    }
    m_fileName = path;

    /*Check if we have saved peaks of this file*/
    QString hashFileName = QString("%1").arg(QString(QCryptographicHash::hash(m_fileName.toUtf8(),QCryptographicHash::Md5).toHex()));
    m_peaksFile = m_peaksDir+"/"+hashFileName+".peak";
}

void PeaksCreator::getPeaks(){
    m_samples.clear();
    QFile peaksFile(m_peaksFile);
    if(peaksFile.exists()) {
        mLoadPeaksFromFile();
    } else {
        loadAudioFile();
    }
}

void PeaksCreator::loadAudioFile()
{
    if(m_fileName.isEmpty()) {
        qDebug() << "Wrong filename";
        return;
    }

    QAudioFormat desiredFormat;
    desiredFormat.setChannelCount(2);
//    desiredFormat.setCodec("audio/x-raw");
    desiredFormat.setSampleFormat(QAudioFormat::UInt8);
//    desiredFormat.setSampleType(QAudioFormat::UnSignedInt);
    desiredFormat.setSampleRate(48000);
//    desiredFormat.setSampleSize(64);

    m_decoder->setSource(m_fileName);
    m_decoder->setAudioFormat(desiredFormat);
    m_decoder->start();
}

void PeaksCreator::mSetBuffer()
{
    m_buffer = m_decoder->read();
    m_audioData.append(m_buffer.constData<char>(), m_buffer.byteCount());
    m_duration += m_buffer.duration();
}

void PeaksCreator::mLoadPeaksFromFile()
{
    m_samples.clear();
    QFile peakFile(m_peaksFile);
    if(!peakFile.exists() || !peakFile.open(QIODevice::ReadOnly)) {
        loadAudioFile();
        return;
    }

    QTextStream peaksRaw(&peakFile);
    QString data = peakFile.readLine();
    QStringList fields = data.split(";");
    foreach(QString value, fields) {
        m_samples.append(value.toDouble());
    };
    emit peaksReady(m_samples);
}

void PeaksCreator::mSavePeaksToFile()
{
    m_samples.clear();
    QFile file(m_peaksFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    m_duration /= 1000*60;

    double bytesInSeconds = m_audioData.size()/(double)m_duration;

    m_duration = m_duration - m_duration%INTERVAL;
    short *buf = (short*)m_audioData.data();

    for (int i = 0; i < m_duration; i+= INTERVAL) {
        double sum = 0;
        double iteratorCount = 0;
        int j = (bytesInSeconds*i);
        double k = j + bytesInSeconds*INTERVAL;

        for (j/=2; j < k/2; j+= 2) {
            sum += qFabs(buf[j]);
            iteratorCount++;
        }

        double outData = sum/iteratorCount;
        out << outData << ";";
        m_samples.append(outData);
    }

    file.close();
    emit peaksReady(m_samples);
}

qreal PeaksCreator::mGetPeakValue(const QAudioFormat &format)
{
    qreal ret(0);
    if (format.isValid()){
        switch (format.sampleFormat()) {
        case QAudioFormat::Unknown:
            break;
        case QAudioFormat::Float:
            ret = 1.00003;
            break;
        case QAudioFormat::UInt8:
            ret = CHAR_MAX;
            break;
        case QAudioFormat::Int16:
            ret = SHRT_MAX;
            break;
        case QAudioFormat::Int32:
            ret = SHRT_MAX;
            break;
        default:
            break;
        }
    }
    return ret;
}
