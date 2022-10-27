/*
 * Copyright (C) 2021-2022 Chupligin Sergey <neochapay@gmail.com>
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

#include "audiofile.h"

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include <QDebug>
#include <QFileInfo>
#include <QIODevice>

AudioFile::AudioFile(QString audiofile, QObject* parent)
    : QObject(parent)
    , fileuri(audiofile)
{
    mediaFile = new QFile(fileuri);
    isValid = false;
    if (!mediaFile->exists()) {
        isValid = false;
        qDebug() << "FNF:" << fileuri;
        emit fileNotFound();
    } else {
        if (mediaFile->open(QIODevice::ReadOnly)) {
            isValid = true;
            loadTags();
        } else {
            qDebug() << "Cant open file:" << fileuri;
            isValid = false;
        }
    }

    mediaFile->close();
}

void AudioFile::loadTags()
{
    if (!isValid) {
        return;
    }

    QScopedPointer<TagLib::FileRef> tagFile(new TagLib::FileRef(fileuri.toUtf8()));

    if (tagFile->isNull()) {
        return;
    }

    TagLib::String t_artist = tagFile->tag()->artist();
    TagLib::String t_title = tagFile->tag()->title();
    TagLib::String t_album = tagFile->tag()->album();
    TagLib::String t_comment = tagFile->tag()->comment();
    TagLib::String t_genre = tagFile->tag()->genre();
    TagLib::uint t_track = tagFile->tag()->track();
    TagLib::uint t_year = tagFile->tag()->year();
    TagLib::uint t_length = tagFile->audioProperties()->length();

    artist = QString::fromStdWString(t_artist.toCWString());
    album = QString::fromStdWString(t_album.toCWString());
    title = QString::fromStdWString(t_title.toCWString());
    comment = QString::fromStdWString(t_comment.toCWString());
    genre = QString::fromStdWString(t_genre.toCWString());

    track = t_track;
    year = t_year;
    length = t_length;

    if (artist.length() < 1) {
        artist = tr("Unknown Artist");
    }

    if (title.length() < 1) {
        title = tr("Unknown Track");
    }
}

bool AudioFile::sync()
{
    if (!isValid) {
        return false;
    }

    QScopedPointer<TagLib::FileRef> tagFile(new TagLib::FileRef(fileuri.toUtf8()));

    if (tagFile->isNull()) {
        return false;
    }

    tagFile->tag()->setAlbum(album.toStdWString());
    tagFile->tag()->setArtist(artist.toStdWString());
    tagFile->tag()->setComment(comment.toStdWString());
    tagFile->tag()->setGenre(genre.toStdWString());
    tagFile->tag()->setTitle(title.toStdWString());
    tagFile->tag()->setTrack(track);
    tagFile->tag()->setYear(year);

    qDebug() << "Saving tags " << fileuri << " " << artist << " " << title << " " << album;
    return tagFile->save();
}

QImage AudioFile::coverImg()
{
    TagLib::MPEG::File file(fileuri.toUtf8());

    TagLib::ID3v2::Tag* m_tag = file.ID3v2Tag(true);
    TagLib::ID3v2::FrameList frameList = m_tag->frameList("APIC");
    if (frameList.isEmpty()) {
        qDebug() << "Cover image from file empty";
        return QImage();
    }

    TagLib::ID3v2::AttachedPictureFrame* coverImg = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frameList.front());
    QImage coverQImg;
    coverQImg.loadFromData((const uchar*)coverImg->picture().data(), coverImg->picture().size());

    return coverQImg;
}

AudioFile::~AudioFile()
{
    mediaFile->close();
}
