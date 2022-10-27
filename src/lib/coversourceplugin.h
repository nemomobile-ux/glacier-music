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

#ifndef COVERSOURCEPLUGIN_H
#define COVERSOURCEPLUGIN_H

#include "glaciermusic_global.h"
#include "track.h"
#include <QImage>
#include <QObject>

class GLACIERMUSIC_EXPORT MusicCoverPlugin : public QObject {
    Q_OBJECT
public:
    virtual bool enabled() = 0;
    virtual QString name() = 0;

    virtual QImage cover() = 0;
    virtual void getCover(Track* track) = 0;
};

Q_DECLARE_INTERFACE(MusicCoverPlugin, "GlacierMusic.CoverPlugin")
#endif // COVERSOURCEPLUGIN_H
