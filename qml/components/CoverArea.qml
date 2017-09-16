import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0

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

    MouseArea{
        id: rewindArea
        width: parent.width
        height: Theme.itemHeightExtraSmall

        anchors{
            left: parent.left
            bottom: parent.bottom
        }

        onClicked: {
            var current_poz = (mouseX-x)/width
            progressBar.width = rewindArea.width*current_poz
        }
    }

    Connections {
        target: rootAudio
        onPositionChanged: {
            progressBar.width = parent.width*(rootAudio.position/rootAudio.duration)
        }
    }
}
