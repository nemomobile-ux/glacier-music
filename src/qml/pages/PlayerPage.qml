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

import org.glacier.music 1.0

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

    Column {
        id: trackInfo
        anchors.fill: parent
        spacing: Theme.itemSpacingSmall

        clip: true

        CoverArea{
            id: coverArea
            width: parent.width
            height: parent.height-trackLabelArea.height-progressItem.height-controsArea.height-Theme.itemSpacingSmall*4

            onCoverChanged: {
                blurredImage.imagePath = cover
            }
        }

        TrackLabelArea{
            id: trackLabelArea
        }

        ProgressItem{
            id: progressItem
            width: parent.width
        }

        ControlsArea{
            id: controsArea
            width: parent.width
        }

    }

    Connections{
        target: nextTrackModel
        function onCurrentIndexChanged(currentIndex) {
            playNextConnection.enabled = false;
            rootAudio.stop();
            var track = nextTrackModel.get(currentIndex);
            if(!track) {
                return;
            }

            trackLabelArea.trackName = track.title
            trackLabelArea.artistsName = track.artist;

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

            mprisPlayer.artist = track.artist
            mprisPlayer.song = track.title
            // Update current song in config file
            if(settings.value("currentTrack") !== track.trackId) {
                settings.setValue("currentTrack", track.trackId);
            }
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
        function onrescanCollectionFinished(prc) {
            if(nextTrackModel.rowCount() < 5) {
                nextTrackModel.updatePlayList();
            }
        }
    }

    function playNext() {
        if(nextTrackModel.rowCount() == 0) {
            nextTrackModel.updatePlayList();
        }

        if(nextTrackModel.currentIndex >= nextTrackModel.rowCount()-1) {
            nextTrackModel.updatePlayList();
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
