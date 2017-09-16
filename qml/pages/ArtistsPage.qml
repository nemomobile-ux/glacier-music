import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0

import org.glacier.music.artistmodel 1.0

Page {
    id: artistPage

    ArtistModel{
        id: artistModel
    }

    ListView{
        id: artistListView
        model: artistModel
        width: parent.width
        height: parent.height
        delegate: ListViewItemWithActions{
            label: name;
        }
    }
}
