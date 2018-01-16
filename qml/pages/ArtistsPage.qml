import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music.artistmodel 1.0

Item{
    id: artistPage

    ArtistModel{
        id: artistModel
    }

    signal viewTracks(int artist_id)

    ListView{
        id: artistListView
        model: artistModel
        width: parent.width
        height: parent.height

        delegate: ListViewItemWithActions{
            label: name
            iconVisible: false

            onClicked: {
                viewTracks(artist_id)
            }
        }
        clip: true
    }
}
