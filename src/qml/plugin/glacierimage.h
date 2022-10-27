#ifndef GLACIERIMAGE_H
#define GLACIERIMAGE_H

#include <QPainter>
#include <QQuickPaintedItem>

class GlacierImage : public QQuickPaintedItem {
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
public:
    explicit GlacierImage(QQuickItem* parent = 0);
    void paint(QPainter* painter);

    QImage image() { return m_image; }
    void setImage(QImage image);

signals:
    void imageChanged(QImage image);

private:
    QImage m_image;
};

#endif // GLACIERIMAGE_H
