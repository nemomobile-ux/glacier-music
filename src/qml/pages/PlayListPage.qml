import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

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
                      pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/LibraryPage.qml"));
                 }
             }
        ]
    }

    ListView{
        id: nextTrack
        anchors.fill: parent

        model: nextTrackModel
        delegate: PlaylistItem{}

        onCurrentIndexChanged: {
            nextTrackModel.currentIndex = currentIndex
        }
    }

}
