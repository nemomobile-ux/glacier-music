import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import "../components"

Page {
    id: mainPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Music")
        tools: [
            ToolButton {
                iconSource: "image://theme/gear"
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/SettingsPage.qml"));
                }
            }
        ]
    }

    BackgroungItem{
        id: bga
        anchors.fill: parent
    }

    Column{
        id: mainColumn
        width: parent.width
        height: parent.height-Theme.itemHeightLarge

        spacing: 40

        ButtonRow{
            id: modeRow
            currentIndex: settings.value("lastPage", 0)
            model: ListModel{
                id: modeButtonsModel
                ListElement{
                    name: qsTr("Favorites")
                }
                ListElement{
                    name: qsTr("Playlists")
                }
                ListElement{
                    name: qsTr("Tracks")
                }
                ListElement{
                    name: qsTr("Albums")
                }
                ListElement{
                    name: qsTr("Artists")
                }
                ListElement{
                    name: qsTr("Folders")
                }
            }
            onCurrentIndexChanged: {
                settings.setValue("lastPage",modeRow.currentIndex)
            }
        }
    }

    Player{
        id: player
        width: parent.width
        height: Theme.itemHeightLarge

        anchors.bottom: bga.bottom
    }
}
