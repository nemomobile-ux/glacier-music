import QtQuick 2.6
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

Item {
    id: progressBar

    Rectangle{
        id: progressBarIndicator
        width: 0
        height: Theme.itemHeightExtraSmall/4
        color: Theme.accentColor
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
                    GradientStop { position: 1.0; color: Theme.accentColor }
                }
            }
        }
    }

    Connections{
        target: rootAudio
        onPositionChanged: {
            progressBarIndicator.width = progressBar.width*(rootAudio.position/rootAudio.duration)
        }
    }

    Item {
        id: progressBarArea
        width: parent.width
        height: Theme.itemHeightExtraSmall/4

        anchors{
            left: parent.left
            bottom: parent.bottom
        }
    }

    MouseArea{
        id: rewindArea
        anchors.fill: progressBarArea

        onClicked: {
            var current_poz = (mouseX-x)/width
            progressBarIndicator.width = rewindArea.width*current_poz
            rootAudio.seek(rootAudio.duration*current_poz)
        }
    }
}
