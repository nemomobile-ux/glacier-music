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

#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <QFile>
#include <QImage>
#include <QObject>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>

class AudioFile : public QObject {
    Q_OBJECT
public:
    explicit AudioFile(QString audiofile, QObject* parent = 0);
    ~AudioFile();

    QString fileuri;

    QString artist;
    QString title;
    QString album;
    QString comment;
    QString genre;
    uint track;
    uint year;
    uint length;

    QImage coverImg();

    bool sync();
    bool isValid;

private:
    QFile* mediaFile;
    void loadTags();

signals:
    void fileNotFound();
    void tagsArrayNotFound();

public slots:
};

#endif // AUDIOFILE_H
