#include "audiofile.h"

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <QFileInfo>
#include <QIODevice>
#include <QDebug>

AudioFile::AudioFile(QString audiofile, QObject *parent) : QObject(parent)
{
    mediaFile = new QFile(audiofile);
    isValid = false;
    if(!mediaFile->exists())
    {
        isValid = false;
        qDebug() << "FNF:" << audiofile;
        emit fileNotFound();
    }
    else
    {
        if(mediaFile->open(QIODevice::ReadWrite))
        {
            isValid = true;
            tagFile = new TagLib::FileRef(QFileInfo(mediaFile->fileName()).absoluteFilePath().toUtf8());
            loadTags();
        }
        else
        {
            qDebug() << "FNRW:" << audiofile;
            isValid = false;
        }
    }
}

void AudioFile::loadTags()
{
    if(!isValid)
    {
        return;
    }
    TagLib::String t_artist = tagFile->tag()->artist();
    TagLib::String t_title = tagFile->tag()->title();
    TagLib::String t_album = tagFile->tag()->album();
    TagLib::String t_comment = tagFile->tag()->comment();
    TagLib::String t_genre = tagFile->tag()->genre();
    TagLib::uint t_track = tagFile->tag()->track();
    TagLib::uint t_year = tagFile->tag()->year();
    TagLib::uint t_length  = tagFile->audioProperties()->length();

    artist = QString(t_artist.toCString(true));
    album = QString(t_album.toCString(true));
    title = QString(t_title.toCString(true));
    comment = QString(t_comment.toCString(true));
    genre = QString(t_genre.toCString(true));
    track = t_track;
    year = t_year;
    length = t_length;

    if(artist.length() < 1)
    {
        artist = "Unknow Artist";
    }

    if(title.length() < 1)
    {
        title = "Unknow Track";
    }
}

bool AudioFile::sync()
{
    if(!isValid)
    {
        return false;
    }
    tagFile->tag()->setAlbum(album.toStdWString());
    tagFile->tag()->setArtist(artist.toStdWString());
    tagFile->tag()->setComment(comment.toStdWString());
    tagFile->tag()->setGenre(genre.toStdWString());
    tagFile->tag()->setTitle(title.toStdWString());
    tagFile->tag()->setTrack(track);
    tagFile->tag()->setYear(year);
    return tagFile->save();
}


AudioFile::~AudioFile()
{
    mediaFile->close();
}
