import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music 1.0

ListViewItemWithActions{
    id: playListItem
    height: Theme.itemHeightHuge

    iconColorized: false

    iconDelegate: GlacierImage{
        image: cover
    }

    label: title
    description: artist
    showNext: false
    selected: (player.trackModel.currentIndex === index)

    actions: [
        ActionButton{
            id: editButton
            iconSource: "image://theme/edit"
            onClicked: {
                pageStack.push(Qt.resolvedUrl("../pages/EditTrackPage.qml"),{track: player.trackModel.get(index)});
            }
        },
        ActionButton{
            id: removeButton
            iconSource: "image://theme/times"
            onClicked: player.trackModel.remove(index)
        }
    ]


    onClicked:{
        player.trackModel.currentIndex = index
    }
}
