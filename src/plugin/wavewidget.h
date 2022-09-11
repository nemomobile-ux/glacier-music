/*
 * Copyright (C) 2022 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef WAVEWIDGET_H
#define WAVEWIDGET_H

#include <QObject>
#include <QtQuick>
#include <QtQml>

class WaveWidget : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString accentColor READ accentColor WRITE setAccentColor NOTIFY accentColorChanged)
    Q_PROPERTY(QString fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(float progress READ progress WRITE setProgress NOTIFY progressChanged)

public:
    explicit WaveWidget(QQuickItem *parent = 0);
    void paint(QPainter *painter);

    QString fileName() {return m_fileName;}
    void setFileName(QString path);

    QString accentColor();
    void setAccentColor(QString color);
    QString fillColor();
    void setFillColor(QString color);

    float progress() {return m_progress;}
    void setProgress(float progress);

signals:
    void fileNameChanged();
    void accentColorChanged();
    void fillColorChanged();
    void progressChanged();

private slots:
    void mUpdateWidget(QVector<double> samples);

private:
    QVector<double> m_samples;

    QString m_fileName;
    QColor m_accentColor;
    QColor m_fillColor;
    float m_progress;
};

#endif // WAVEWIDGET_H
