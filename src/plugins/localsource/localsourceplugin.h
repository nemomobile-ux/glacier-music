/*
 * Copyright (C) 2022-2025 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef LOCALSOURCEPLUGIN_H
#define LOCALSOURCEPLUGIN_H

#include "collection.h"
#include "tracksmodel.h"

#include <musicsourceplugin.h>

class LocalSourcePlugin : public MusicSourcePlugin {
    Q_OBJECT
    Q_INTERFACES(MusicSourcePlugin)
    Q_PLUGIN_METADATA(IID "GlacierMusic.SourcePlugin")
public:
    LocalSourcePlugin(QObject* parent = nullptr);
    virtual ~LocalSourcePlugin();

    bool enabled() { return true; }
    QString name() { return tr("Local music database"); }
    QString id() { return "localsource"; }

    bool hasBack();
    void setHasBack(bool hasBack);

    bool hasForward();
    void setHasForward(bool hasForward);

    TracksModel* tracksModel();
    void loadPlaylist(PlayMode mode, QString param);
    void clearPlaylist();

private slots:
    void calcButtonStatus();
    void loadCurrentPlayList();
    void complementPlayList();
    void makeTrackPlayed(int id);

private:
    TracksModel* m_tracksModel;
    Collection* m_collection;
    QThread* m_rescanTread;

    bool m_hasBack;
    bool m_hasForward;
};

#endif // LOCALSOURCEPLUGIN_H
