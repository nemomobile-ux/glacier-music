import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

ListViewItemWithActions{
    id: playListItem
    width: parent.width
    height: Theme.itemHeightHuge
    iconColorized: false

    icon: cover != "" ? cover : "image://theme/music"
    label: title
    description: artist
    showNext: false

    actions: [
        ActionButton{
            id: editButton
            iconSource: "image://theme/edit"
            onClicked: {
                pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/EditTrackPage.qml"),{trackId:trackId});
            }
        },
        ActionButton{
            id: removeButton
            iconSource: "image://theme/times"
            onClicked: nextTrackModel.remove(index)
        }
    ]

    Rectangle{
        visible: (nextTrack.currentIndex == index)
        width: parent.width
        height: 1
        color: Theme.accentColor
        anchors.bottom: parent.bottom
    }

    onClicked:{
        nextTrack.currentIndex = index
    }
}
