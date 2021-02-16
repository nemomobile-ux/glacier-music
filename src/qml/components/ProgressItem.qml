/*
 * Copyright (C) 2021 Chupligin Sergey <neochapay@gmail.com>
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

import org.glacier.music.widgets 1.0

Item {
    id: progressItem
    width: parent.width
    height: Theme.itemHeightMedium

    WaveWidget{
        id: lineOfProgress
        width: parent.width-Theme.itemSpacingSmall*2
        height: Theme.itemHeightExtraSmall/3

        anchors{
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: Theme.itemSpacingSmall
        }

        accentColor: Theme.accentColor
        fillColor: Theme.fillColor
        progress: rootAudio.position/rootAudio.duration

        MouseArea{
            id: rewindArea
            anchors.fill: parent

            onClicked: {
                var current_poz = (mouseX-x)/width
                rootAudio.seek(rootAudio.duration*current_poz)
            }
        }
    }

    Label{
        id: startSec
        text: "0:00"

        font.pixelSize: Theme.fontSizeTiny/2

        anchors{
            left: parent.left
            leftMargin: Theme.itemSpacingSmall
            bottom: parent.bottom
            bottomMargin: Theme.itemSpacingSmall
        }
    }

    Label{
        id: endSec
        text: "9:99"

        font.pixelSize: Theme.fontSizeTiny/2

        anchors{
            right: parent.right
            rightMargin: Theme.itemSpacingSmall
            bottom: parent.bottom
            bottomMargin: Theme.itemSpacingSmall
        }
    }

    Connections {
        target: rootAudio
        onPositionChanged: {
            startSec.text = formatIime(rootAudio.position)
            endSec.text = formatIime(rootAudio.duration-rootAudio.position)
        }
    }

    Connections{
        target: nextTrackModel
        onCurrentIndexChanged: {
            lineOfProgress.fileName = nextTrackModel.get(currentIndex).fileName;
        }
    }

    function formatIime(ms) {
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
