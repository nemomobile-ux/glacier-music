/*
 * Copyright (C) 2021-2025 Chupligin Sergey <neochapay@gmail.com>
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

import org.glacier.music 1.0

Page {
    id: tracksPage
    property int artistId: 0
    property string artistName: ""

    headerTools: HeaderToolsLayout {
        id: tools
        title: artistId == 0 ? qsTr("Tracks") : artistName
        showBackButton: true;
    }

    ListView{
        id: tracksListView
        width: parent.width
        height: parent.height
        delegate: ListViewItemWithActions{
            id: trackItem
            label: artistId == 0 ? artist_name+" "+title : title
            description: ((track !== 0) ? track : "") +
                         ((track !== 0) && (album !== "") ? " - " : "") +
                         album
            icon: "image://theme/music"
            showNext: false

            onClicked: nextTrackModel.addItem(track_id, 0)

            actions: [
                ActionButton{
                    id: trackItemActions
                    iconSource: "image://theme/edit"

                }
            ]
        }

        clip: true
    }

    ScrollDecorator {
        flickable: tracksListView
    }

    Component.onCompleted: {
        trackModel.setArtist(artistId);
    }
}
