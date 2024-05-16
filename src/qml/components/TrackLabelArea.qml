/*
 * Copyright (C) 2022-2024 Chupligin Sergey <neochapay@gmail.com>
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

Item {
    id: trackLabelArea
    width: parent.width
    height: Theme.itemHeightExtraLarge
    clip: true

    property string trackName: qsTr("Unknown track")
    property string artistsName: qsTr("Unknown artist")

    Label {
        id: track
        text: trackLabelArea.trackName
        anchors{
            top: parent.top
            left: parent.left
            leftMargin: Theme.itemSpacingSmall
        }

        font{
            bold: true
            pixelSize: trackLabelArea.height/2
        }
        color: Theme.textColor
    }

    Label {
        id: artists
        text: trackLabelArea.artistsName
        anchors{
            top: track.bottom
            left: parent.left
            leftMargin: Theme.itemSpacingSmall
        }

        font.pixelSize: trackLabelArea.height/4
        color: Theme.accentColor

        MouseArea{
            anchors.fill: parent
            onClicked: {
                pageStack.push(Qt.resolvedUrl("../pages/TracksPage.qml"),
                               {artistId: nextTrackModel.get(nextTrackModel.currentIndex).artist_id,
                                   artistName: nextTrackModel.get(nextTrackModel.currentIndex).artist});
            }
        }
    }
}
