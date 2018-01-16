import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music.trackmodel 1.0

Page {
    id: artistPage
    property int artistId: 0

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Tracks")
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
            label: artist_name+" "+title;
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
