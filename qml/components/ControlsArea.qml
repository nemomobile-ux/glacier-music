import QtQuick 2.6
import QtMultimedia 5.5

import QtQuick.Controls 1.0 //needed for the Stack attached property
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

Rectangle{
    id: controsArea

    color: "transparent"

    signal playPauseClicked()
    signal playlistClicked()
    signal backCliked()
    signal forwardClicled()

    Image{
        id: playlistBtn
        width: playPauseBtn.width*0.6
        height: width

        anchors{
            right: parent.right
            rightMargin: width
            verticalCenter: playPauseBtn.verticalCenter
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                playlistClicked()
            }
        }
        source: "image://theme/align-justify"
    }

    Image{
        id: forwBtn
        width: playPauseBtn.width*0.6
        height: width

        anchors{
            right: playlistBtn.left
            rightMargin: width/2
            verticalCenter: playPauseBtn.verticalCenter
        }

        source: "image://theme/forward"

        MouseArea{
            anchors.fill: parent
            onClicked: forwardClicled()// playNext()
        }
    }

    Image{
        id: playPauseBtn
        width: height
        height: parent.width/9

        anchors{
            right: forwBtn.left
            rightMargin: width/2
            verticalCenter: parent.verticalCenter
        }

        source: player.isPlayed ?
                    "image://theme/pause" :
                    "image://theme/play"

        MouseArea{
            anchors.fill: parent
            onClicked: {
               playPauseClicked();
            }
        }
    }

    Image{
        id: backBtn
        width: playPauseBtn.width*0.6
        height: width

        visible: nextTrackModel.currentIndex !== 0

        anchors{
            right: playPauseBtn.left
            rightMargin: playPauseBtn.width/2
            verticalCenter: playPauseBtn.verticalCenter
        }

        MouseArea{
            anchors.fill: parent
            onClicked: backCliked()// playPrev()
        }

        source: "image://theme/backward"
    }
}
