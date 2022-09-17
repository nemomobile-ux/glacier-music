#ifndef BLURREDIMAGE_H
#define BLURREDIMAGE_H

#include <QPainter>
#include <QQuickPaintedItem>

class BlurredImage : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

public:
    explicit BlurredImage(QQuickItem* parent = 0);
    void paint(QPainter* painter);

    QString imagePath() { return m_imagePath; }
    void setImagePath(QString path);

    int radius() { return m_radius; }
    void setRadius(int radius);

    qreal opacity() { return m_opacity; }
    void setOpacity(qreal opacity);

signals:
    void imagePathChanged();
    void radiusChanged();
    void opacityChanged();

private:
    QImage makeBlurred(QImage& image, const QRect& rect, int radius, bool alphaOnly = false);
    QString m_imagePath;
    int m_radius;
    qreal m_opacity;
};

#endif // BLURREDIMAGE_H
