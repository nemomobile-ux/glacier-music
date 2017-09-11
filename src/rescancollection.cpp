#include <QAudioFormat>

#include "rescancollection.h"
#include "audiofile.h"

RescanCollection::RescanCollection(QObject *parent) : QObject(parent)
{
    dba = new dbAdapter();
}

void RescanCollection::scan()
{
    qDebug() << "Start rescan collection";

    //Yes i know about flac, cue and etc...i add it later. Or you can create pr
    QStringList allowedExtensions;
    allowedExtensions << "*.mp3" << "*.ogg";

    QStringList scanDir = aviableDirs();
    QStringList aviableFiles;

    QSqlDatabase db = dba->instance().db;
    QSqlQuery query(db);

    for(int i=0; i<scanDir.count(); i++)
    {
        QDirIterator it(scanDir[i],allowedExtensions, QDir::Files, QDirIterator::Subdirectories);
        for (;it.hasNext(); it.next())
        {
            aviableFiles << it.next();
        }
    }

    double m_aviableFiles = aviableFiles.count();
    double m_scannedFiles = 0;

    query.exec("UPDATE files SET `updated` = '0'");

    for(int i=0; i<aviableFiles.count();i++)
    {

        QString file = aviableFiles[i];
        AudioFile *aFile = new AudioFile(file);
        if(!aFile->isValid)
        {
            continue;
        }

        QString str = QString("SELECT path FROM files WHERE `path`='%1'").arg(file);
        bool ok = query.exec(str);
        if(!ok)
        {
            qDebug() << query.lastQuery() << query.lastError().text();
        }

        if(query.next())
        {
            //File in collection
            QString str = QString("UPDATE files SET `updated` = 1 WHERE `path`='%1'").arg(file);
            bool ok = query.exec(str);
            if(!ok)
            {
                qDebug() << query.lastQuery() << query.lastError().text();
            }
        }
        else
        {
            //New file
            qDebug() << "New file" << file;
            QString str = QString("INSERT INTO files (path) VALUES ('%1')").arg(file);
            bool ok = query.exec(str);
            if(!ok)
            {
                qDebug() << query.lastQuery() << query.lastError().text();
            }
            else
            {
                emit newFile(file);
            }
        }
        m_scannedFiles++;

        double prc = m_scannedFiles/m_aviableFiles*100;
        emit scanProcess(QVariant(prc));
    }

    QString str = QString("DELETE FROM files WHERE `updated` = '0'");
    bool ok = query.exec(str);
    if(!ok)
    {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}

QStringList RescanCollection::aviableDirs()
{
    QStringList aviableDirs;
    //Add download dir
    aviableDirs << QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).first();

    //Add standart music path
    if(QDir(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first()).exists())
    {
        aviableDirs << QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first();
        qDebug() << aviableDirs.last();
    }
    //Find sdcard
    QDir mountDir("/media/sdcard/");
    mountDir.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    for (int i=0; i < mountDir.entryList().count(); i++)
    {
        aviableDirs << mountDir.absolutePath() +"/"+ mountDir.entryList().at(i);
        qDebug() << aviableDirs.last();
    }

    return aviableDirs;
}
