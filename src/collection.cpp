#include "collection.h"
#include "rescancollection.h"
#include "dbadapter.h"

#include <QDir>
#include <QStandardPaths>

#include <QDebug>

Collection::Collection(QObject *parent) : QObject(parent)
{
    m_firstRun = false;
    m_cacheLocation = QDir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    if(!m_cacheLocation.exists())
    {
        m_firstRun = true;
        m_cacheLocation.mkpath(m_cacheLocation.absolutePath()+"/images/");
    }

    dba = new dbAdapter();

    connect(dba,SIGNAL(baseCreate()),this,SLOT(rescanCollection()));
}


Collection::~Collection()
{
    //    thread->quit();
}

void Collection::rescanCollection()
{
    RescanCollection *rCollection = new RescanCollection();

    QThread *rescanThread = new QThread;
    connect(rescanThread,SIGNAL(started()),rCollection, SLOT(scan()));
    connect(rCollection,SIGNAL(scanProcess(QVariant)),this,SLOT(m_rescanCollectionProgress(QVariant)));
    rCollection->moveToThread(rescanThread);
    rescanThread->start();
}


void Collection::m_rescanCollectionProgress(QVariant prc)
{
    emit updateRescanProgress(prc);
}
