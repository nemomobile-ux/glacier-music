import QtQuick 2.6
import QtMultimedia 5.5

import QtQuick.Controls 1.0 //needed for the Stack attached property
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

Rectangle{
    id: controsArea
    height: Theme.itemHeightHuge

    color: "transparent"

    Image{
        id: playlistBtn
        width: playPauseBtn.width*0.6
        height: width

        anchors{
            right: backBtn.left
            rightMargin: width
            verticalCenter: playPauseBtn.verticalCenter
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/PlayListPage.qml"));
            }
        }

        source: "image://theme/align-justify"
    }

    Image{
        id: backBtn
        width: playPauseBtn.width*0.6
        height: width

        anchors{
            right: playPauseBtn.left
            rightMargin: width/2
            verticalCenter: playPauseBtn.verticalCenter
        }

        MouseArea{
            anchors.fill: parent
            onClicked: playPrev()
        }

        source: "image://theme/backward"
    }

    Image{
        id: playPauseBtn
        width: height
        height: parent.width/9

        anchors.centerIn: parent;

        source: (rootAudio.playbackState == MediaPlayer.PlayingState) ?
                    "image://theme/pause" :
                    "image://theme/play"

        MouseArea{
            anchors.fill: parent
            onClicked: playPause();
        }
    }

    Image{
        id: forwBtn
        width: playPauseBtn.width*0.6
        height: width

        anchors{
            left: playPauseBtn.right
            leftMargin: width/2
            verticalCenter: playPauseBtn.verticalCenter
        }

        source: "image://theme/forward"

        MouseArea{
            anchors.fill: parent
            onClicked: playNext()
        }
    }

    Image{
        id: soundBtn
        width: playPauseBtn.width*0.6
        height: width

        anchors{
            left: forwBtn.right
            leftMargin: width
            verticalCenter: playPauseBtn.verticalCenter
        }

        source: "image://theme/volume-up"

        MouseArea{
            anchors.fill: parent
            onClicked: {
                volumeArea.visible = true
                removeVolumeTimer.start()
            }
        }
    }

    Rectangle{
        id: volumeArea
        width: parent.width
        height: parent.height

        color: Theme.backgroundColor

        visible: false

        MouseArea{
            anchors.fill: parent
            onClicked: volumeArea.visible = false
        }

        Slider{
            id: volumeSlider

            width: parent.width*0.8
            anchors.centerIn: parent

            minimumValue: 0
            maximumValue: 1
            stepSize: 0.05
            value: rootAudio.volume

            onValueChanged:{
                removeVolumeTimer.restart()
                rootAudio.volume = value
            }
        }
    }

    Timer{
        id: removeVolumeTimer
        interval: 5000
        onTriggered: {
            volumeArea.visible = false
        }
    }
}
