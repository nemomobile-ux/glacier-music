import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

ListViewItemWithActions{
    id: playListItem
    width: parent.width
    height: Theme.itemHeightHuge

    icon: ""
    label: artist+" - "+title

    actions: Rectangle {
        id: playListItemActions
        width: playListItem.height*2
        height: playListItem.height

        color: "transparent"

        Image{
            id: editButton
            width: parent.height*0.6
            height: width

            anchors{
                left: parent.left
                leftMargin: parent.height*0.2
                top: parent.top
                topMargin: parent.height*0.2
            }

            source: "/usr/share/themes/glacier/fontawesome/icons/edit.png"
        }

        Image{
            id: removeButton
            width: parent.height*0.6
            height: width

            anchors{
                left: editButton.right
                leftMargin: parent.height*0.4
                top: parent.top
                topMargin: parent.height*0.2
            }

            source: "/usr/share/themes/glacier/fontawesome/icons/times.png"
        }
    }

    onClicked:{
        nextTrack.currentIndex = index
    }
}
