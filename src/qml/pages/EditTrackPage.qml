import QtQuick 2.6

import QtQuick.Controls 1.0 //needed for the Stack attached property
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0


import org.glacier.music.trackmodel 1.0
import "../components"

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
                text: track.title
                font.bold: true
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: track.artist
                color:  Theme.accentColor
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: track.album
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: (track.track !== 0) ? track.track : ''
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: track.genre
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: (track.year !== 0) ? track.year : ''
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: track.comment
                width: parent.width
                wrapMode: Text.Wrap
            }
            Label {
                text: formatTimeSeconds(track.length)
                width: parent.width
                wrapMode: Text.Wrap
            }

        }
    }

    function formatTimeSeconds(s) {
        var m = Math.floor(s / 60);
        s = s % 60;
        return ((m > 9) ? m : "0"+ m) + ":" + ((s > 9) ? s : "0"+s)

    }

    ScrollDecorator {
        flickable: flickable
    }

    onTrackChanged: {
        console.log(JSON.stringify(track, null, 2))
    }
}
