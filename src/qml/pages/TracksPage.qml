import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music.trackmodel 1.0

Page {
    id: artistPage
    property int artistId: 0
    property string artistName: ""

    headerTools: HeaderToolsLayout {
        id: tools
        title: artistId == 0 ? qsTr("Tracks") : artistName
        showBackButton: true;
    }

    TrackModel{
        id: trackModel
    }

    ListView{
        id: artistListView
        model: trackModel
        width: parent.width
        height: parent.height
        delegate: ListViewItemWithActions{
            id: trackItem
            label: artistId == 0 ? artist_name+" "+title : title
            description: ((track !== 0) ? track : "") +
                         ((track !== 0) && (album !== "") ? " - " : "") +
                         album
            icon: "image://theme/music"
            showNext: false

            onClicked: nextTrackModel.addItem(track_id, 0)

            actions: [
                ActionButton{
                    id: trackItemActions
                    iconSource: "image://theme/edit"

                }
            ]
        }

        clip: true
    }

    Component.onCompleted: {
        if(artistId != 0) {
            trackModel.setArtist(artistId);
        }
    }
}
