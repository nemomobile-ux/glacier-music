#include "blurredimage.h"

#include <QImage>

BlurredImage::BlurredImage(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , m_imagePath("/usr/share/glacier-music/images/cover.png")
    , m_radius(50)
    , m_opacity(0.5)
{
}

void BlurredImage::paint(QPainter* painter)
{
    QSizeF itemSize = size();
    QRectF target(0, 0, itemSize.width(), itemSize.height());
    QImage source(m_imagePath);
    QImage blurr = makeBlurred(source, source.rect(), m_radius);

    painter->drawImage(target, blurr);

    painter->setBrush(QBrush("#000000"));
    painter->setOpacity(m_opacity);
    painter->drawRect(target);
}

void BlurredImage::setImagePath(QString qml_path)
{
    if (qml_path == m_imagePath) {
        return;
    }

    QUrl path = qml_path;
    QFile imgFile(path.toLocalFile());
    if (!imgFile.exists()) {
        qWarning() << "Not exists!!!" << path;
        return;
    }

    m_imagePath = path.toLocalFile();
    emit imagePathChanged();
    update();
}

void BlurredImage::setRadius(int radius)
{
    if (radius != m_radius) {
        m_radius = radius;
        emit radiusChanged();
        update();
    }
}

void BlurredImage::setOpacity(qreal opacity)
{
    if (opacity != m_opacity) {
        m_opacity = opacity;
        emit opacityChanged();
        update();
    }
}

QImage BlurredImage::makeBlurred(QImage& image, const QRect& rect, int radius, bool alphaOnly)
{
    int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
    int alpha = (radius < 1) ? 16 : (radius > 17) ? 1
                                                  : tab[radius - 1];

    QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    int r1 = rect.top();
    int r2 = rect.bottom();
    int c1 = rect.left();
    int c2 = rect.right();

    int bpl = result.bytesPerLine();
    int rgba[4];
    unsigned char* p;

    int i1 = 0;
    int i2 = 3;

    if (alphaOnly) {
        i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);
    }

    for (int col = c1; col <= c2; col++) {
        p = result.scanLine(r1) + col * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p += bpl;
        for (int j = r1; j < r2; j++, p += bpl)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = result.scanLine(row) + c1 * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p += 4;
        for (int j = c1; j < c2; j++, p += 4)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int col = c1; col <= c2; col++) {
        p = result.scanLine(r2) + col * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p -= bpl;
        for (int j = r1; j < r2; j++, p -= bpl)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = result.scanLine(row) + c2 * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p -= 4;
        for (int j = c1; j < c2; j++, p -= 4)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    return result;
}
