#include "glacierimage.h"

GlacierImage::GlacierImage(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , m_image(QImage())
{
}

void GlacierImage::paint(QPainter* painter)
{
    QSizeF itemSize = size();
    QRectF target(0, 0, itemSize.width(), itemSize.height());

    painter->drawImage(target, m_image);
}

void GlacierImage::setImage(QImage image)
{
    if (image != m_image && !image.isNull()) {
        m_image = image;
        emit imageChanged(m_image);
        update();
    }
}
