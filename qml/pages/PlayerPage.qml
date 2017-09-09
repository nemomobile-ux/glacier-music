import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0

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

        Rectangle{
            id: coverArea
            width: parent.width
            height: width

            Image{
                id: cover
                source: "/usr/share/glacier-music/images/cover.jpg"
                width: parent.width
                height: parent.height
            }

            Rectangle{
                id: progressBar
                width: parent.width*0.4
                height: Theme.itemHeightExtraSmall/4
                color: "#0091e5"
                anchors{
                    left: parent.left
                    bottom: parent.bottom
                }

                Item{
                    id: gdr
                    height: Theme.itemHeightExtraSmall/2
                    width: (height*4 < parent.width) ? parent.width : height*4
                    anchors{
                        right: parent.right
                        bottom: parent.top

                    }

                    LinearGradient {
                        anchors.fill: parent
                        start: Qt.point(parent.width/2, parent.height/2)
                        end: Qt.point(parent.width, parent.height)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "transparent" }
                            GradientStop { position: 1.0; color: "#0091e5" }
                        }
                    }
                }
            }
        }

        Rectangle{
            id: trackLabelArea
            width: parent.width
            height: Theme.fontSizeLarge*2+Theme.itemSpacingLarge*2

            color: "transparent"

            Label{
                id: trackLabel
                text: "Би-2 - Иномарки"
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

                source: "/usr/share/themes/glacier/fontawesome/icons/backward.png"
            }

            Image{
                id: playPause
                width: parent.height*0.6
                height: width

                anchors.centerIn: parent;

                source: "/usr/share/themes/glacier/fontawesome/icons/pause.png"
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

            ListModel{
                id: nextTrackModel
                ListElement{
                    cover: "/usr/share/glacier-music/images/cover.jpg"
                    artist: "Би-2"
                    track: "Революция"
                }
                ListElement{
                    cover: "/usr/share/glacier-music/images/cover.jpg"
                    artist: "Би-2"
                    track: "Песок"
                }
                ListElement{
                    cover: "/usr/share/glacier-music/images/cover.jpg"
                    artist: "Би-2"
                    track: "Сердце на волоске"
                }
            }

            ListView{
                id: nextTrack
                width: parent.width
                height: parent.height
                model: nextTrackModel
                delegate: Item{
                    width: parent.width
                    height: Theme.itemHeightHuge

                    Image{
                        id: coverImage
                        source: cover
                        width: parent.height
                        height: parent.height
                    }

                    Label{
                        text: artist+" - "+track
                        width: parent.width-cover.width
                        font{
                            bold: true
                            pixelSize: Theme.fontSizeExtraLarge
                        }
                        anchors{
                            left: coverImage.right
                            leftMargin: coverImage.height/2
                        }

                        verticalAlignment: Text.AlignVCenter
                    }
                }

            }
        }
    }
}
