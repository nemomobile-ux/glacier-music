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
import QtQuick.Layouts

import Nemo
import Nemo.Controls


import org.glacier.music 1.0

Page {
    id: libraryPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Library")
        showBackButton: true;
    }

    TabBar {
        id: bar
        width: parent.width

        TabButton {
            text: qsTr("Artists")
        }
        TabButton {
            text: qsTr("Tracks")
        }
    }

    StackLayout {
        width: parent.width
        height: parent.height - bar.height

        currentIndex: bar.currentIndex

        anchors{
            top: bar.bottom
        }

        ArtistsPage{
            onViewTracks: {
                pageStack.push(Qt.resolvedUrl("../pages/TracksPage.qml"), {artistId: artist_id, artistName: artist_name});
            }
        }
        TracksPage{
        }
    }
}
