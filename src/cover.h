#ifndef COVER_H
#define COVER_H

#include <QObject>
#include "track.h"

class Cover : public QObject
{
    Q_OBJECT
public:
    explicit Cover(QObject *parent = 0);

signals:
    void coverReady(QString coverFile);

public slots:
    void getCoverByTrackId(int trackId);

private slots:
    void m_coverReady(QString coverFile);

private:
    QString m_coverDir;
    Track *m_track;
};

#endif // COVER_H
