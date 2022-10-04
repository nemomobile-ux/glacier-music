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

import QtQuick 2.6
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music 1.0

import "../components"

Page {
    id: playerPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Music")
        tools: [
            ToolButton {
                iconSource: "image://theme/gear"
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("../pages/SettingsPage.qml"));
                }
            }
        ]
    }

    BlurredImage{
        id: blurredImage
        anchors.fill: parent
        image: player.cover
    }

    Column {
        id: trackInfo
        anchors.fill: parent
        spacing: Theme.itemSpacingSmall

        clip: true

        CoverArea{
            id: coverArea
            width: parent.width
            height: parent.height-trackLabelArea.height-progressItem.height-controsArea.height-Theme.itemSpacingSmall*4
        }

        TrackLabelArea{
            id: trackLabelArea
        }

        ProgressItem{
            id: progressItem
            width: parent.width
        }

        ControlsArea{
            id: controsArea
            width: parent.width
        }

    }

    Connections{
        target: player.trackModel
        function onCurrentIndexChanged(currentIndex) {
            var track = player.trackModel.get(currentIndex);
            if(!track) {
                console.log("Wrong track")
                return;
            }

            trackLabelArea.trackName = track.title
            trackLabelArea.artistsName = track.artist;

            mprisPlayer.artist = track.artist
            mprisPlayer.song = track.title
        }
    }

    Connections{
        target: mprisPlayer
        function onNextRequested() { player.trackModel.currentIndex++ }
        function onPreviousRequested() { player.trackModel.currentIndex-- }
        function onPlayRequested() { player.playPause() }
        function onPauseRequested() { player.pause() }
        function onPlayPauseRequested() { player.playPause() }
    }
}
