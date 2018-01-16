import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music.cover 1.0

import "../components"

Page {
    id: playerPage

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

    Flickable{
        id: mainFlickable
        anchors.fill: parent
        contentHeight: coverArea.height+trackLabelArea.height+controsArea.height+nextTrack.height

        CoverArea{
            id: coverArea
        }

        Rectangle{
            id: trackLabelArea
            width: parent.width
            height: Theme.fontSizeLarge*2+Theme.itemSpacingLarge*2
            anchors.top: coverArea.bottom
            color: "transparent"

            Label{
                id: trackLabel
                text: ""
                anchors.fill: parent
                font{
                    bold: true
                    pixelSize: Theme.fontSizeExtraLarge
                }
                scale: paintedWidth > width ? (width / paintedWidth) : 1
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        ControlsArea{
            id: controsArea
            width: parent.width
            anchors.top: trackLabelArea.bottom
        }



        ListView{
            id: nextTrack
            width: parent.width
            height: contentHeight
            model: nextTrackModel
            delegate: PlaylistItem{}
            anchors.top: controsArea.bottom
            clip: true

            onCurrentIndexChanged: {
                coverArea.cover = "/usr/share/glacier-music/images/cover.png";
                coverArea.cover = (nextTrackModel.get(currentIndex).cover) ? nextTrackModel.get(currentIndex).cover : "/usr/share/glacier-music/images/cover.png"
                coverLoader.getCoverByTrackId(nextTrackModel.get(currentIndex).trackId)
                rootAudio.stop();
                trackLabel.text = nextTrackModel.get(currentIndex).artist+"\n"+nextTrackModel.get(currentIndex).title
                rootAudio.source = nextTrackModel.get(currentIndex).fileName

                rootAudio.play();
                nextTrackModel.setPlayed(currentIndex)

                mprisPlayer.artist = nextTrackModel.get(currentIndex).artist
                mprisPlayer.song = nextTrackModel.get(currentIndex).title
            }
        }
    }

    Cover{
        id: coverLoader
    }

    Connections{
        target: rootAudio
        onStopped: playNext()
    }

    Connections{
        target: coverLoader
        onCoverReady: {
            coverArea.cover = coverFile;
        }
    }

    Connections{
        target: mprisPlayer
        onNextRequested: playNext()
        onPreviousRequested: --nextTrack.currentIndex
        onPlayRequested: rootAudio.play();
        onPauseRequested: rootAudio.pause();
    }


    Connections{
        target: collection
        onUpdateRescanProgress: {
            if(nextTrack.count < 5)
            {
                nextTrackModel.formatRandomPlaylist(1);
            }
        }
    }

    function playNext()
    {
        console.log((nextTrack.currentIndex+1) + " | " + nextTrack.count)
        if((nextTrack.currentIndex+1) >= nextTrack.count)
        {
            nextTrackModel.formatRandomPlaylist(1);
        }
        ++nextTrack.currentIndex
    }
}
