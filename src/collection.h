#ifndef COLLECTION_H
#define COLLECTION_H

#include "dbadapter.h"

#include <QObject>
#include <QDir>

class Collection : public QObject
{
    Q_OBJECT
public:
    explicit Collection(QObject *parent = 0);
    Q_INVOKABLE bool isFirstRun(){return m_firstRun;}
    ~Collection();

signals:
    void newFile(QString path);
    void updateRescanProgress(QVariant prc);
    void noMusicFiles();

public slots:
    void rescanCollection();

private slots:
    void m_rescanCollectionProgress(QVariant prc);

private:
    bool m_firstRun;
    QStringList aviableDirs();
    QThread *m_rescanThread;
};

#endif // COLLECTION_H
