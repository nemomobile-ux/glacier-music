import QtQuick 2.0
import QtMultimedia 5.5

Rectangle{
    id: controsArea

    color: "transparent"

    Image{
        id: playlistBtn
        width: playPause.width*0.6
        height: width

        anchors{
            right: backBtn.left
            rightMargin: width
            verticalCenter: playPauseBtn.verticalCenter
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/LibraryPage.qml"));
            }
        }

        source: "/usr/share/themes/glacier/fontawesome/icons/align-justify.png"
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
            onClicked: nextTrack.currentIndex--
        }

        source: "/usr/share/themes/glacier/fontawesome/icons/backward.png"
    }

    Image{
        id: playPauseBtn
        width: parent.height*0.6
        height: width

        anchors.centerIn: parent;

        source: (rootAudio.playbackState == MediaPlayer.PlayingState) ?
                    "/usr/share/themes/glacier/fontawesome/icons/pause.png" :
                    "/usr/share/themes/glacier/fontawesome/icons/play.png"

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

        source: "/usr/share/themes/glacier/fontawesome/icons/forward.png"

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

        source: "/usr/share/themes/glacier/fontawesome/icons/volume-up.png"
    }

    Connections{
        target: mprisPlayer
        onPlayPauseRequested: playPause();
    }

    function playPause(){
        if(rootAudio.playbackState == MediaPlayer.PlayingState)
        {
            rootAudio.pause();
        }
        else
        {
            rootAudio.play()
        }
    }
}
