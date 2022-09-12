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

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music 1.0

Row {
    id: progressItem
    width: parent.width-Theme.itemSpacingSmall*2
    height: Theme.itemHeightMedium
    spacing: Theme.itemSpacingSmall

    anchors{
        left: parent.left
        leftMargin: Theme.itemSpacingSmall
    }

    Label{
        id: startSec
        text: "00:00"

        font.pixelSize: Theme.fontSizeTiny
        anchors.verticalCenter: parent.verticalCenter
    }

    WaveWidget{
        id: lineOfProgress
        width: parent.width-Theme.itemSpacingSmall*4-startSec.paintedWidth-endSec.paintedWidth
        height: Theme.itemHeightExtraSmall/3

        anchors{
            verticalCenter: parent.verticalCenter
        }

        accentColor: Theme.accentColor
        fillColor: Theme.fillColor
        progress: player.progress

        MouseArea{
            id: rewindArea
            anchors.fill: parent

            onClicked: {
                var current_poz = (mouseX-x)/width
                player.seek(player.duration*current_poz)
            }
        }
    }

    Label{
        id: endSec
        text: "99:99"

        font.pixelSize: Theme.fontSizeTiny

        anchors.verticalCenter: parent.verticalCenter
    }

    Connections {
        target: player
        function onPositionChanged() {
            startSec.text = formatTime(player.position)
            endSec.text = formatTime(player.duration-player.position)
        }
    }

    Connections{
        target: nextTrackModel
        function onCurrentIndexChanged(currentIndex) {
            lineOfProgress.fileName = nextTrackModel.get(currentIndex).fileName;
        }
    }

    function formatTime(ms) {
        var out = ""

        if(ms >= 3600000) {
            var hours = Math.trunc(ms/3600000);
            out += hours+":"
            ms = ms-hours*3600000
        }

        if(ms >= 60000) {
            var min = Math.trunc(ms/60000);
            if(min < 10 ) {
                out += "0"+min+":"
            }
            ms = ms-min*60000
        } else {
            out += "00:"
        }

        var sec = Math.trunc(ms/1000)
        if(sec < 10) {
            out += "0"+sec;
        } else {
            out += sec
        }

        return out;
    }
}
