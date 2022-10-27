/*
 * Copyright (C) 2022 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef FROMTAGSCOVERPLUGIN_H
#define FROMTAGSCOVERPLUGIN_H

#include <QVariant>
#include <coversourceplugin.h>

class FromTagsCoverPlugin : public MusicCoverPlugin {
    Q_OBJECT
    Q_INTERFACES(MusicCoverPlugin)
    Q_PLUGIN_METADATA(IID "GlacierMusic.CoverPlugin")
public:
    FromTagsCoverPlugin();
    bool enabled() { return true; }
    QString name() { return tr("Load cover from tags"); }

    QImage cover() { return m_coverImage; }
    void getCover(Track* track);

private:
    QImage m_coverImage = QImage("image://theme/music");
};

#endif // FROMTAGSCOVERPLUGIN_H
