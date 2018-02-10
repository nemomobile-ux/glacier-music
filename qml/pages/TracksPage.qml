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
        title: artistId == 0 ? qsTr("Tracks") : qsTr(artistName)
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
            description: track+" - "+album
            icon: "image://theme/music"
            showNext: false

            onClicked: nextTrackModel.addItem(track_id, 0)

            actions: Rectangle {
                id: trackItemActions
                width: trackItem.height
                height: trackItem.height

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

                    source: "image://theme/edit"
                }
            }
        }
        clip: true
    }

    Component.onCompleted: {
        if(artistId != 0)
        {
            trackModel.setArtist(artistId);
        }
    }
}
