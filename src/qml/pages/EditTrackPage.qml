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

import QtQuick
import Nemo.Controls

import org.glacier.music 1.0
import "../components"

Page {
    id: editTrackPage

    property variant track

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Edit track info")
        showBackButton: true;
    }

    Flickable {
        id: flickable
        anchors.fill: parent;
        contentHeight: childrenRect.height
        Column {
            width: parent.width
            Image {
                source: String(track.cover).startsWith("/") ? "file://"+track.cover : track.cover
                width: parent.width
                fillMode: Image.PreserveAspectFit
            }
            Label {
                text: track.title
                font.bold: true
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: track.artist
                color:  Theme.accentColor
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: track.album
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: (track.track !== 0) ? track.track : ''
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: track.genre
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: (track.year !== 0) ? track.year : ''
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: track.comment
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: formatTimeSeconds(track.length)
                width: parent.width
                wrapMode: Text.Wrap
            }

        }
    }

    function formatTimeSeconds(s) {
        var m = Math.floor(s / 60);
        s = s % 60;
        return ((m > 9) ? m : "0"+ m) + ":" + ((s > 9) ? s : "0"+s)

    }

    ScrollDecorator {
        flickable: flickable
    }

    onTrackChanged: {
        console.log(JSON.stringify(track, null, 2))
    }
}
