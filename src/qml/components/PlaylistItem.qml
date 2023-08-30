import QtQuick
import Nemo.Controls

ListViewItemWithActions{
    id: playListItem
    height: Theme.itemHeightHuge
    iconColorized: false

    icon: cover !== "" ?  (String(cover).startsWith("/")  ? "file://"+cover : cover ) : "image://theme/music"
    label: title
    description: artist
    showNext: false
    selected: (nextTrack.currentIndex === index)

    actions: [
        ActionButton{
            id: editButton
            iconSource: "image://theme/edit"
            onClicked: {
                pageStack.push(Qt.resolvedUrl("../pages/EditTrackPage.qml"),{track: nextTrack.model.get(index)});
            }
        },
        ActionButton{
            id: removeButton
            iconSource: "image://theme/times"
            onClicked: nextTrackModel.remove(index)
        }
    ]


    onClicked:{
        nextTrack.currentIndex = index
    }
}
