import QtQuick
import Nemo.Controls

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
                      pageStack.push(Qt.resolvedUrl("../pages/LibraryPage.qml"));
                 }
             },
             ToolButton {
                 iconSource: "file:///usr/share/glacier-music/images/erasier.svg"
                 onClicked: {
                     nextTrackModel.clearPlaylist();
                 }
             }

        ]
    }

    ListView{
        id: nextTrack
        anchors.fill: parent

        model: nextTrackModel
        delegate: PlaylistItem{
            width: nextTrack.width
        }
        currentIndex: nextTrackModel.currentIndex

        onCurrentIndexChanged: {
            nextTrackModel.currentIndex = currentIndex
        }
    }

    ScrollDecorator {
        flickable: nextTrack
    }

}
