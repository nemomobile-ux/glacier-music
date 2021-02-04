#include "collection.h"
#include "rescancollection.h"
#include "dbadapter.h"

#include <QDir>
#include <QStandardPaths>

#include <QDebug>

Collection::Collection(QObject *parent) : QObject(parent)
{
    m_firstRun = false;
    QDir cacheLocation = QDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    QFile dbFile(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/db.sql");

    if(!cacheLocation.exists() || !dbFile.exists()) {
        m_firstRun = true;
        cacheLocation.mkpath(cacheLocation.absolutePath()+"/images/");
    }

    dbAdapter* dba = new dbAdapter();
    connect(dba,SIGNAL(baseCreate()),this,SLOT(rescanCollection()));
}


Collection::~Collection()
{
    m_rescanThread->quit();
}

void Collection::rescanCollection()
{
    RescanCollection *rCollection = new RescanCollection();

    m_rescanThread = new QThread;
    connect(m_rescanThread,SIGNAL(started()),rCollection, SLOT(scan()));
    connect(rCollection,SIGNAL(scanProcess(QVariant)),this,SLOT(m_rescanCollectionProgress(QVariant)));
    connect(rCollection,SIGNAL(noMusicFiles()),this,SIGNAL(noMusicFiles()));
    rCollection->moveToThread(m_rescanThread);
    m_rescanThread->start();
}


void Collection::m_rescanCollectionProgress(QVariant prc)
{
    emit updateRescanProgress(prc);
}
