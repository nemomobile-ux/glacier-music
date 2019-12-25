import QtQuick 2.6
import QtMultimedia 5.5
import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.nemomobile.settings 1.0

Rectangle{
    id: player
    color: Theme.backgroundColor

    property bool isPlayed

    Component.onCompleted: {
        isPlayed = settings.value("isPlayed",0);
        if(isPlayed == 1) {
            rootAudio.play()
        }
    }

    onIsPlayedChanged: {
        settings.setValue("isPlayed", isPlayed)
    }

    Image{
        id: coverArea

        height: player.height*0.8
        width: player.height*0.8


        source: "/usr/share/glacier-music/images/cover.png"

        anchors{
            left: player.left
            top: player.top

            topMargin: player.height*0.1
            leftMargin: player.height*0.1
        }

        Connections{
            target: nextTrackModel
            onCurrentIndexChanged:{
                var currentItremCover = nextTrackModel.get(nextTrackModel.currentIndex).cover
                if(currentItremCover != "") {
                    coverArea.source = currentItremCover;
                } else {
                    coverArea.source =  "/usr/share/glacier-music/images/cover.png"
                }
            }
        }
    }

    Item{
        id: trackLabel
        width: parent.width-coverArea.width-controlsArea.width-player.height*0.2
        height: player.height*0.8

        anchors{
            top: parent.top
            left: coverArea.right
            topMargin: player.height*0.1
            leftMargin: player.height*0.1
        }

        Text{
            id: trackName
            color: Theme.textColor
            font.pixelSize: player.height/3

            anchors{
                top: parent.top
                left: parent.left
            }

            Connections{
                target: nextTrackModel
                onCurrentIndexChanged: {
                    trackName.text = nextTrackModel.get(currentIndex).title
                }
            }
        }

        Text{
            id: artistName
            color: Theme.textColor
            font.pixelSize: player.height/4

            anchors{
                top: trackName.bottom
                left: parent.left

                topMargin: player.height*0.1
            }

            Connections{
                target: nextTrackModel
                onCurrentIndexChanged: {
                    artistName.text = nextTrackModel.get(currentIndex).artist
                }
            }
        }

        MouseArea{
            anchors.fill: parent
            onPressAndHold: {
                console.log("Open edit page")
            }
        }
    }

    ControlsArea{
        id: controlsArea
        width: parent.height*4
        height: parent.height

        anchors{
            right: parent.right
            top: parent.top
        }

        onPlayPauseClicked: {
            if(player.isPlayed == 1)
            {
                player.isPlayed = 0
                rootAudio.pause();
            }
            else
            {
                player.isPlayed = 1
                rootAudio.play()
            }
        }

        onForwardClicled: {
            if(nextTrackModel.currentIndex >= nextTrackModel.rowCount()-1)
            {
                nextTrackModel.formatRandomPlaylist(1);
            }
            ++nextTrackModel.currentIndex
            rootAudio.play()
        }

        onBackCliked: {
            if(nextTrackModel.currentIndex != 0){
                --nextTrackModel.currentIndex
            }
            rootAudio.play()
        }

        onPlaylistClicked: {
            pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/PlayListPage.qml"));
        }
    }

    ProgressBarIndicator{
        width: parent.width
        height: Theme.itemHeightExtraSmall

        anchors{
            left: parent.left
            bottom: parent.bottom
        }
    }
}
