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

import "../components"

Page {
    id: playListPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Playlist")
        showBackButton: true;

         tools: [
             ToolButton {
                 iconSource: "image://theme/book"
                 onClicked: {
                      pageStack.push(Qt.resolvedUrl("../pages/LibraryPage.qml"));
                 }
             },
             ToolButton {
                 iconSource: "file:///usr/share/glacier-music/images/erasier.svg"
                 onClicked: {
                     player.trackModel.clearPlaylist();
                 }
             }

        ]
    }

    ListView{
        id: nextTrack
        anchors.fill: parent

        model: player.trackModel
        delegate: PlaylistItem{
            width: nextTrack.width
        }
        currentIndex: player.trackModel.currentIndex

        onCurrentIndexChanged: {
            player.trackModel.currentIndex = currentIndex
        }
    }

    ScrollDecorator {
        flickable: nextTrack
    }

}
