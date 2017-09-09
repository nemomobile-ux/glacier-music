#ifndef RESCANCOLLECTION_H
#define RESCANCOLLECTION_H

#include <QObject>
#include "dbadapter.h"

class RescanCollection : public QObject
{
    Q_OBJECT
public:
    explicit RescanCollection(QObject *parent = 0);

signals:
    void newFile(QString path);
    void scanProcess(QVariant prc);

public slots:
    void scan();

private:
    dbAdapter* dba;

    QStringList aviableDirs();
};

#endif // RESCANCOLLECTION_H
