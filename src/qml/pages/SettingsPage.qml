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

Page {
    id: settingsPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Settings")
        showBackButton: true;
    }

    ListModel{
        id: fileOrganizeModel
        ListElement { name: qsTr("Only in interal storage") }
        ListElement { name: qsTr("Yes") }
        ListElement { name: qsTr("No") }
    }

    Column {
        id: fileSortingRow
        width: parent.width
        anchors{
            top: parent.top
            topMargin: Theme.itemSpacingLarge
        }

        ListViewItemWithActions{
            id: pushToPlugins
            label: qsTr("Plugins")
            icon: "image://theme/cubes"
            onClicked: pageStack.push(Qt.resolvedUrl("SettingsPluginPage.qml"))
        }

        GlacierRoller {
            id: fileOrganize
            width: parent.width

            clip: true
            model: fileOrganizeModel
            label: qsTr("Enable file sorting")
            delegate: GlacierRollerItem {
                Text {
                    height: fileOrganize.itemHeight
                    text: name
                    color: Theme.textColor
                    font.pixelSize: Theme.fontSizeMedium
                    font.bold: (fileOrganize.activated && fileOrganize.currentIndex === index)
                }
            }
            onCurrentIndexChanged:{
                settings.setValue("sorting",fileOrganizeModel.get(fileOrganize.currentIndex).name);
            }
        }


        CheckBox {
            text:  qsTr("Always play from the beginning")
            anchors {
                left: parent.left
                leftMargin: height
            }
            checked: settings.value("alwaysFromTheBeginning",1) === 1
            onClicked: {
                if(checked) {
                    settings.setValue("alwaysFromTheBeginning",1)
                } else {
                    settings.setValue("alwaysFromTheBeginning",0)
                }
                console.warn(settings.value("alwaysFromTheBeginning",1))
            }
        }
    }
}
