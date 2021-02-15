#ifndef WAVEWIDGET_H
#define WAVEWIDGET_H

#include <QObject>
#include <QtQuick>
#include <QtQml>

class WaveWidget : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString accentColor READ accentColor WRITE setAccentColor NOTIFY accentColorChanged)
    Q_PROPERTY(QString fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(float progress READ progress WRITE setProgress NOTIFY progressChanged)

public:
    explicit WaveWidget(QQuickItem *parent = 0);
    void paint(QPainter *painter);

    QString accentColor();
    void setAccentColor(QString color);
    QString fillColor();
    void setFillColor(QString color);

    float progress() {return m_progress;}
    void setProgress(float progress);


signals:
    void accentColorChanged();
    void fillColorChanged();
    void progressChanged();

private:
    QColor m_accentColor;
    QColor m_fillColor;
    float m_progress;

};

#endif // WAVEWIDGET_H
