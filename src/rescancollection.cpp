#include <QAudioFormat>

#include "rescancollection.h"
#include "track.h"

RescanCollection::RescanCollection(QObject *parent) : QObject(parent)
{

}

void RescanCollection::scan()
{
    qDebug() << "Start rescan collection";

    //Yes i know about flac, cue and etc...i add it later. Or you can create pr
    QStringList allowedExtensions;
    allowedExtensions << "*.mp3" << "*.ogg";

    QStringList scanDir = aviableDirs();
    QStringList aviableFiles;

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

    for(int i=0; i<aviableFiles.count();i++)
    {

        QString file = aviableFiles[i];
        Track *track = new Track(file);
        m_scannedFiles++;

        double prc = m_scannedFiles/m_aviableFiles*100;
        emit scanProcess(QVariant(prc));
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
