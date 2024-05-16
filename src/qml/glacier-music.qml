/*
 * Copyright (C) 2021-2024 Chupligin Sergey <neochapay@gmail.com>
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

import QtQuick
import QtQuick.Controls

import Nemo
import Nemo.Controls

import org.nemomobile.settings 1.0
import org.nemomobile.mpris 1.0

import org.glacier.music 1.0

import Nemo.Dialogs 1.0

import "pages"

ApplicationWindow {
    id: root

    property int cameraId: 0
    property string fileName: ""

    property var iso;

    Settings{
        id: settings;
    }

/*    Cover{
        id: coverLoader
    }*/

    initialPage: PlayerPage{}

    Component.onCompleted: {
        if(player.isFirstRun)
        {
            pageStack.push(Qt.resolvedUrl("../pages/SettingsPage.qml"));
        }
    }

    Connections{
        target: player
        function onNoMusicFiles() {
            noMusicDialog.visible = true
        }
    }

    MprisPlayer {
        id: mprisPlayer

        property string artist: qsTr("Loading")
        property string song: qsTr("tags...")

        serviceName: "glacier-music"
        identity: "Glacier Music"
        supportedUriSchemes: ["file"]
        supportedMimeTypes: ["audio/x-wav", "audio/x-vorbis+ogg", "audio/mpeg"]

        canControl: true

        canGoNext: true
        canGoPrevious: true
        canPause: player.state == 1
        canPlay: player.state != 1
        canSeek: false

        playbackStatus: (player.state == 1) ? Mpris.Playing : Mpris.Paused

        onArtistChanged: {
            var metadata = mprisPlayer.metadata
            metadata[Mpris.metadataToString(Mpris.Artist)] = [artist] // List of strings
            mprisPlayer.metadata = metadata
        }

        onSongChanged: {
            var metadata = mprisPlayer.metadata
            metadata[Mpris.metadataToString(Mpris.Title)] = song // String
            mprisPlayer.metadata = metadata
        }
    }

    QueryDialog {
        id: noMusicDialog
        visible: false
        inline: false

        icon: "image://theme/exclamation-triangle"

        cancelText: qsTr("Cancel")
        acceptText: qsTr("Ok")
        headingText: qsTr("No music files found")
        subLabelText: qsTr("Please add music files into Music or Download directory. Or connect card with music")

        onSelected: {
            Qt.quit()
        }
    }
}
