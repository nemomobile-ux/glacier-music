/*
 * Copyright (C) 2021-2022 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music.widgets 1.0

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
                    pageStack.push(Qt.resolvedUrl("../pages/SettingsPage.qml"));
                }
            }
        ]
    }

    BlurredImage{
        id: blurredImage
        anchors.fill: parent
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

        Item {
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

            Label {
                id: trackName
                text: qsTr("Unknown track")
                anchors{
                    top: parent.top
                    left: parent.left
                }

                font{
                    bold: true
                    pixelSize: Theme.fontSizeSmall
                }
            }

            Label {
                id: artistsName
                text: qsTr("Unknown artist")
                anchors{
                    top: trackName.bottom
                    left: parent.left
                }
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.accentColor

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log(nextTrackModel.get(nextTrackModel.currentIndex).artist_id)
                        console.log(nextTrackModel.get(nextTrackModel.currentIndex).artist)

                        pageStack.push(Qt.resolvedUrl("../pages/TracksPage.qml"),
                                       {artistId: nextTrackModel.get(nextTrackModel.currentIndex).artist_id,
                                        artistName: nextTrackModel.get(nextTrackModel.currentIndex).artist});
                    }
                }
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
        id: playNextConnection
        target: rootAudio
        function onStopped() { playNext() }
    }

    Connections{
        target: nextTrackModel
        function onCurrentIndexChanged(currentIndex) {
            playNextConnection.enabled = false;
            rootAudio.stop();
            var track = nextTrackModel.get(currentIndex);

            trackName.text = track.title
            artistsName.text = track.artist;
            rootAudio.source = "file://" + track.fileName
            // Set seek of first playing song and play only if old state is playing
            if(currentIndex === 0 && settings.value("currentTrack") === track.trackId) {
                rootAudio.seek(settings.value("seek"))
                if(settings.value("playbackState") === 1) {
                    rootAudio.play();
                }
            } else {
                rootAudio.play();
            }
            playNextConnection.enabled = true;

            nextTrackModel.setPlayed(currentIndex)

            mprisPlayer.artist = track.artist
            mprisPlayer.song = track.title
            // Update current song in config file
            if(settings.value("currentTrack") !== track.trackId) {
                settings.setValue("currentTrack", track.trackId);
            }
            // Change cover
            var cover = track.cover;
            if (cover !== "") {
                cover = String(cover).startsWith("/") ? "file://" + cover : cover;
                coverArea.cover = cover;
                blurredImage.imagePath = cover;
            } else {
                coverArea.cover = "file:///usr/share/glacier-music/images/cover.png";
                blurredImage.imagePath = "file:///usr/share/glacier-music/images/cover.png";
                coverLoader.getCoverByTrackId(track.trackId)
            }
        }
    }

    Connections{
        target: coverLoader
        function onCoverReady() {
            coverArea.cover = coverFile
        }
        function onCoverLoaing() {
            /*FIXME add loader*/
            coverArea.cover = "file:///usr/share/glacier-music/images/cover.png";
        }
    }

    Connections{
        target: mprisPlayer
        function onNextRequested() { playNext() }
        function onPreviousRequested() { playPrev() }
        function onPlayRequested() { rootAudio.play() }
        function onPauseRequested() { rootAudio.pause() }
        function onPlayPauseRequested() { playPause() }
    }


    Connections{
        target: collection
        function onUpdateRescanProgress(prc) {
            if(nextTrackModel.rowCount() < 5) {
                nextTrackModel.formatRandomPlaylist(1);
            }
        }
    }

    function playNext() {
        console.log("playNext(): " + (nextTrackModel.currentIndex+1) + " | " + nextTrackModel.rowCount())
        if(nextTrackModel.currentIndex >= nextTrackModel.rowCount()-1) {
            nextTrackModel.formatRandomPlaylist(1);
        }
        ++nextTrackModel.currentIndex
    }

    function playPrev() {
        if(nextTrackModel.currentIndex !== 0){
            --nextTrackModel.currentIndex
        }
    }

    function playPause() {
        if(rootAudio.playbackState == MediaPlayer.PlayingState) {
            rootAudio.pause();
        } else {
            if(rootAudio.source == "") {
                playNext()
            }

            rootAudio.play()
        }
    }
}
