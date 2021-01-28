import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

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

    CoverArea{
        id: coverArea
        width: height
        height: Math.min(parent.height-trackLabelArea.height-controsArea.height-Theme.itemSpacingHuge*4, parent.width-Theme.itemSpacingHuge)
        anchors{
            top: parent.top
            topMargin: Theme.itemSpacingHuge
            horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle{
        id: trackLabelArea
        width: parent.width-Theme.itemSpacingHuge*2
        height: Theme.fontSizeLarge*2+Theme.itemSpacingLarge*2

        anchors{
            bottom: controsArea.top
            bottomMargin: Theme.itemSpacingHuge
            left: parent.left
            leftMargin: Theme.itemSpacingHuge
        }

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
        anchors{
            bottom: parent.bottom
            bottomMargin: Theme.itemSpacingHuge
        }
    }

    Connections{
        target: rootAudio
        onStopped: playNext()
    }

    Connections{
        target: nextTrackModel
        onCurrentIndexChanged: {
            rootAudio.stop();
            trackLabel.text = nextTrackModel.get(currentIndex).artist+"\n"+nextTrackModel.get(currentIndex).title
            rootAudio.source = nextTrackModel.get(currentIndex).fileName

/*Set seek of firs playing dong and play only if old state is playing*/
            if(currentIndex == 0 && settings.value("currentTrack") == nextTrackModel.get(currentIndex).trackId)
            {
                rootAudio.seek(settings.value("seek"))
                if(settings.value("playbackState") == 1)
                {
                    rootAudio.play();
                }
            }
            else
            {
                rootAudio.play();
            }
            nextTrackModel.setPlayed(currentIndex)

            mprisPlayer.artist = nextTrackModel.get(currentIndex).artist
            mprisPlayer.song = nextTrackModel.get(currentIndex).title
/*Update current song in config file */
            if(settings.value("currentTrack") != nextTrackModel.get(currentIndex).trackId)
            {
                settings.setValue("currentTrack",nextTrackModel.get(currentIndex).trackId);
            }
        }
    }

    Connections{
        target: mprisPlayer
        onNextRequested: playNext()
        onPreviousRequested: playPrev()
        onPlayRequested: rootAudio.play();
        onPauseRequested: rootAudio.pause();
        onPlayPauseRequested: playPause();
    }


    Connections{
        target: collection
        onUpdateRescanProgress: {
            if(nextTrackModel.rowCount() < 5)
            {
                nextTrackModel.formatRandomPlaylist(1);
            }
        }
    }

    function playNext()
    {
        console.log((nextTrackModel.currentIndex+1) + " | " + nextTrackModel.rowCount())
        if(nextTrackModel.currentIndex >= nextTrackModel.rowCount()-1)
        {
            nextTrackModel.formatRandomPlaylist(1);
        }
        ++nextTrackModel.currentIndex
    }

    function playPrev()
    {
        if(nextTrackModel.currentIndex != 0){
            --nextTrackModel.currentIndex
        }
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
