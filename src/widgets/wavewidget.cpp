#include "wavewidget.h"
#include "../peakscreator.h"

WaveWidget::WaveWidget(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_fileName("")
    , m_accentColor(QColor("#0091e5"))
    , m_fillColor(QColor("#474747"))
    , m_progress(0)

{
}

void WaveWidget::paint(QPainter *painter)
{
    QBrush fillBrush(m_fillColor);
    QBrush accentBrush(m_accentColor);

    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);

    QSizeF itemSize = size();
    float lineHeight = itemSize.height()/3;
    /* If not load peaks file */
    if(m_samples.count() < 5) {
        painter->setBrush(fillBrush);
        /*line to end*/
        painter->drawRoundedRect(0,
                                 0+lineHeight,
                                 itemSize.width()-lineHeight,
                                 lineHeight,
                                 lineHeight/2,
                                 lineHeight/2);

        painter->setBrush(accentBrush);
        /*Point of progress*/
        painter->drawEllipse(QRect((itemSize.width()-itemSize.height())*m_progress,
                                   0,
                                   itemSize.height(),
                                   itemSize.height()
                                   ));
        /*line from start*/
        painter->drawRoundedRect(0,
                                 0+lineHeight,
                                 itemSize.width()*m_progress,
                                 lineHeight,
                                 lineHeight/2,
                                 lineHeight/2);
    } else {
        /*if have peaks */
        int samples = m_samples.count();
        double max = max = *std::max_element(m_samples.begin(), m_samples.end());

        int lineWidth = (int)(itemSize.width()/samples);
        for (int i = 0; i < samples; i++) {
            int progressInParts = floor(itemSize.width()*m_progress/lineWidth);
            if(progressInParts > i) { //before now 
                painter->setBrush(accentBrush);
            } else if(progressInParts < i) {
                painter->setBrush(fillBrush);
            }
            
            if(progressInParts == i) {
                // NEED TO FIX VIEW
                painter->setBrush(accentBrush);
                double partProgress = itemSize.width()*m_progress/lineWidth-floor(itemSize.width()*m_progress/lineWidth);
                painter->drawRoundedRect(lineWidth*i,
                                     (itemSize.height()-itemSize.height()*m_samples[i]/max)/2,
                                     itemSize.width()/samples*partProgress,
                                     itemSize.height()*m_samples[i]/max,
                                     lineHeight/2,
                                     lineHeight/2);
                painter->setBrush(fillBrush);
                painter->drawRoundedRect(lineWidth*i+itemSize.width()/samples*partProgress,
                                     (itemSize.height()-itemSize.height()*m_samples[i]/max)/2,
                                     itemSize.width()/samples*(1-partProgress),
                                     itemSize.height()*m_samples[i]/max,
                                     lineHeight/2,
                                     lineHeight/2);
            } else {
                painter->drawRoundedRect(lineWidth*i,
                                     (itemSize.height()-itemSize.height()*m_samples[i]/max)/2,
                                     itemSize.width()/samples,
                                     itemSize.height()*m_samples[i]/max,
                                     lineHeight/2,
                                     lineHeight/2);
            }
        }
    }
}

QString WaveWidget::accentColor()
{
    return m_accentColor.name();
}

QString WaveWidget::fillColor()
{
    return m_fillColor.name();
}

void WaveWidget::setAccentColor(QString color)
{
    QColor nColor(color);
    if(nColor.isValid() && nColor != m_accentColor) {
        m_accentColor = nColor;
        emit accentColorChanged();
        update();
    }
}

void WaveWidget::setFillColor(QString color)
{
    QColor nColor(color);
    if(nColor.isValid() && nColor != m_fillColor) {
        m_fillColor = nColor;
        emit fillColorChanged();
        update();
    }
}

void WaveWidget::setProgress(float progress)
{
    if(progress >= 0 && progress <= 1 && progress != m_progress) {
        m_progress = progress;
        emit progressChanged();
        update();
    }
}

void WaveWidget::setFileName(QString path)
{
    QThread *readPeaksThread = new QThread();
    PeaksCreator *pCreator = new PeaksCreator();
    pCreator->setFileName(path);

    pCreator->moveToThread(readPeaksThread);
    connect(readPeaksThread, &QThread::started,
            pCreator, &PeaksCreator::getPeaks);
    connect(pCreator, &PeaksCreator::peaksReady,
            this, &WaveWidget::mUpdateWidget);
    readPeaksThread->start();
}

void WaveWidget::mUpdateWidget(QVector<double> samples)
{
    m_samples = samples;
    update();
}

