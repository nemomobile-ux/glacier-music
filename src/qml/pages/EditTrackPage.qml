import QtQuick 2.6

import QtQuick.Controls 1.0 //needed for the Stack attached property
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0


import org.glacier.music.trackmodel 1.0

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
                text: track.trackId
            }
            Label {
                text: track.title
                font.bold: true
            }
            Label {
                text: track.artist
                color:  Theme.accentColor
            }
        }
    }

    ScrollDecorator {
        flickable: flickable
    }

    onTrackChanged: {
        console.log(JSON.stringify(track, null, 2))
    }
}
