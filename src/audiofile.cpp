#include "audiofile.h"

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <QFileInfo>
#include <QIODevice>
#include <QDebug>

AudioFile::AudioFile(QString audiofile, QObject *parent) : QObject(parent),
fileuri(audiofile)
{
    mediaFile = new QFile(fileuri);
    isValid = false;
    if(!mediaFile->exists())
    {
        isValid = false;
        qDebug() << "FNF:" << fileuri;
        emit fileNotFound();
    }
    else
    {
        if(mediaFile->open(QIODevice::ReadOnly))
        {
            isValid = true;
            loadTags();
        }
        else
        {
            qDebug() << "Cant open file:" << fileuri;
            isValid = false;
        }
    }

    mediaFile->close();
}

void AudioFile::loadTags()
{
    if(!isValid)
    {
        return;
    }

    QScopedPointer<TagLib::FileRef> tagFile(new TagLib::FileRef(fileuri.toUtf8()));

    if(tagFile->isNull())
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

    artist = QString::fromStdWString(t_artist.toCWString());
    album = QString::fromStdWString(t_album.toCWString());
    title = QString::fromStdWString(t_title.toCWString());
    comment = QString::fromStdWString(t_comment.toCWString());
    genre = QString::fromStdWString(t_genre.toCWString());

    track = t_track;
    year = t_year;
    length = t_length;

    if(artist.length() < 1)
    {
        artist = "Unknown Artist";
    }

    if(title.length() < 1)
    {
        title = "Unknown Track";
    }
}

bool AudioFile::sync()
{
    if(!isValid)
    {
        return false;
    }

    QScopedPointer<TagLib::FileRef> tagFile(new TagLib::FileRef(fileuri.toUtf8()));

    if(tagFile->isNull())
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
