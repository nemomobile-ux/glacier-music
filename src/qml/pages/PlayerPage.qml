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

    Rectangle {
        id: trackInfo
        width: parent.width
        height: parent.height-progressItem.height-controsArea.height

        color: "transparent"
        clip: true

        CoverArea{
            id: coverArea
            width: isUiPortrait ? height : Theme.itemHeightExtraLarge
            height: isUiPortrait ? trackInfo.height-trackLabelArea.height : Theme.itemHeightExtraLarge
            anchors{
                top: isUiPortrait ? parent.top : trackLabelArea.top
                topMargin: isUiPortrait ? Theme.itemSpacingSmall : undefined
                horizontalCenter: isUiPortrait ? parent.horizontalCenter : undefined
                right: isUiPortrait ? undefined : trackLabelArea.left
                rightMargin: isUiPortrait ? undefined : Theme.itemSpacingSmall
            }
        }

        Item{
            id: trackLabelArea
            width: isUiPortrait ? parent.width-Theme.itemSpacingSmall*2 : parent.width-Theme.itemSpacingSmall*2-coverArea.width
            height: Theme.itemHeightExtraLarge

            anchors{
                top: isUiPortrait ? coverArea.bottom : undefined
                left:  isUiPortrait ? parent.left : undefined
                right: isUiPortrait ? undefined : parent.right
                leftMargin: isUiPortrait ? Theme.itemSpacingSmall : undefined
                rightMargin: isUiPortrait ? undefined : Theme.itemSpacingSmall
            }

            Label{
                id: trackName
                text: "Unknow track"
                anchors{
                    top: parent.top
                    left: parent.left
                }

                font{
                    bold: true
                    pixelSize: Theme.fontSizeSmall
                }
            }

            Label{
                id: artistsName
                text: "Unknow artist"
                anchors{
                    top: trackName.bottom
                    left: parent.left
                }
                font{
                    pixelSize: Theme.fontSizeTiny
                }
                color: Theme.accentColor
            }
        }
    }

    ProgressItem{
        id: progressItem
        width: parent.width
        anchors{
            bottom: controsArea.top
        }
    }

    ControlsArea{
        id: controsArea
        width: parent.width
        anchors{
            bottom: parent.bottom
            bottomMargin: Theme.itemSpacingSmall
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

            trackName.text = nextTrackModel.get(currentIndex).title
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
