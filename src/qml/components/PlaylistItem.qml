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

import org.glacier.music 1.0

ListViewItemWithActions{
    id: playListItem
    height: Theme.itemHeightHuge

    iconColorized: false

    iconDelegate: GlacierImage{
        image: cover
    }

    label: title
    description: artist
    showNext: false
    selected: (player.trackModel.currentIndex === index)

    actions: [
        ActionButton{
            id: editButton
            iconSource: "image://theme/edit"
            onClicked: {
                pageStack.push(Qt.resolvedUrl("../pages/EditTrackPage.qml"),{track: player.trackModel.get(index)});
            }
        },
        ActionButton{
            id: removeButton
            iconSource: "image://theme/times"
            onClicked: player.trackModel.remove(index)
        }
    ]


    onClicked:{
        player.trackModel.currentIndex = index
    }
}
