import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0
import QtQuick.Window 2.1

import "../components"

Page {
    id: cameraPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Music")
        tools: [
            ToolButton {
                iconSource: "/usr/share/themes/glacier/fontawesome/icons/gear.png"
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/SettingsPage.qml"));
                }
            }
        ]
    }

    Column{
        width: parent.width
        anchors{
            top: parent.top
        }

        CoverArea{
            id: coverArea
        }

        Rectangle{
            id: trackLabelArea
            width: parent.width
            height: Theme.fontSizeLarge*2+Theme.itemSpacingLarge*2

            color: "transparent"

            Label{
                id: trackLabel
                text: ""
                anchors.fill: parent
                font{
                    bold: true
                    pixelSize: Theme.fontSizeExtraLarge
                }
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Rectangle{
            id: controsArea
            width: parent.width
            height: trackLabelArea.height*2

            color: "transparent"

            Image{
                id: playlistBtn
                width: playPause.width*0.6
                height: width

                anchors{
                    right: backBtn.left
                    rightMargin: width
                    verticalCenter: playPause.verticalCenter
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
                width: playPause.width*0.6
                height: width

                anchors{
                    right: playPause.left
                    rightMargin: width/2
                    verticalCenter: playPause.verticalCenter
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: nextTrack.currentIndex--
                }

                source: "/usr/share/themes/glacier/fontawesome/icons/backward.png"
            }

            Image{
                id: playPause
                width: parent.height*0.6
                height: width

                anchors.centerIn: parent;

                source: (rootAudio.playbackState == MediaPlayer.PlayingState) ?
                            "/usr/share/themes/glacier/fontawesome/icons/pause.png" :
                            "/usr/share/themes/glacier/fontawesome/icons/play.png"

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
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
            }

            Image{
                id: forwBtn
                width: playPause.width*0.6
                height: width

                anchors{
                    left: playPause.right
                    leftMargin: width/2
                    verticalCenter: playPause.verticalCenter
                }

                source: "/usr/share/themes/glacier/fontawesome/icons/forward.png"

                MouseArea{
                    anchors.fill: parent
                    onClicked: nextTrack.currentIndex++
                }
            }

            Image{
                id: soundBtn
                width: playPause.width*0.6
                height: width

                anchors{
                    left: forwBtn.right
                    leftMargin: width
                    verticalCenter: playPause.verticalCenter
                }

                source: "/usr/share/themes/glacier/fontawesome/icons/volume-up.png"
            }
        }

        Rectangle{
            id: nextArea
            width: parent.width
            height: root.height-tools.height-coverArea.height-trackLabelArea.height-controsArea.height

            color: "transparent"

            ListView{
                id: nextTrack
                width: parent.width
                height: parent.height
                model: nextTrackModel
                delegate: PlaylistItem{}

                clip: true

                onCurrentIndexChanged: {
                    console.log(nextTrackModel.get(currentIndex).fileName)
                    rootAudio.stop();
                    trackLabel.text = nextTrackModel.get(currentIndex).artist+" - "+nextTrackModel.get(currentIndex).title
                    rootAudio.source = nextTrackModel.get(currentIndex).fileName
                    rootAudio.play();
                }

                highlightRangeMode: ListView.StrictlyEnforceRange
            }
        }
    }
}
