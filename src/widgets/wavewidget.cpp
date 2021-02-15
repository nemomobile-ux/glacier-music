#include "wavewidget.h"


WaveWidget::WaveWidget(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_accentColor(QColor("#0091e5"))
    , m_fillColor(QColor("#474747"))
    , m_progress(0)

{

}

void WaveWidget::paint(QPainter *painter)
{
    QBrush fillBrush(m_fillColor);
    QBrush accentBrush(m_accentColor);

    painter->setBrush(fillBrush);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);

    QSizeF itemSize = size();
    float lineHeight = itemSize.height()/3;
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
