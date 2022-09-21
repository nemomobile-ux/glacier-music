#ifndef BLURREDIMAGE_H
#define BLURREDIMAGE_H

#include <QPainter>
#include <QQuickPaintedItem>

class BlurredImage : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

public:
    explicit BlurredImage(QQuickItem* parent = 0);
    void paint(QPainter* painter);

    QString source() { return m_source; }
    void setSource(QString source);

    QImage image() { return m_image; }
    void setImage(QImage image);

    int radius() { return m_radius; }
    void setRadius(int radius);

    qreal opacity() { return m_opacity; }
    void setOpacity(qreal opacity);

signals:
    void sourceChanged();
    void radiusChanged();
    void opacityChanged();
    void imageChanged();

private:
    QImage makeBlurred(QImage& image, const QRect& rect, int radius, bool alphaOnly = false);
    QString m_source;
    QImage m_image;
    int m_radius;
    qreal m_opacity;
};

#endif // BLURREDIMAGE_H
