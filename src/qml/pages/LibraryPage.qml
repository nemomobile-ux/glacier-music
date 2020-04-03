import QtQuick 2.6

import QtQuick.Controls 1.0 //needed for the Stack attached property
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0


import org.glacier.music.trackmodel 1.0

Page {
    id: libraryPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Library")
        showBackButton: true;
    }

    TabView {
        anchors.fill: parent

        Tab {
            title: "Artists"
            ArtistsPage{
                onViewTracks: {
                    pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/TracksPage.qml"), {artistId: artist_id, artistName: artist_name});
                }
            }
        }
        Tab {
            title: "Tracks"
            TracksPage{}
        }
    }
}
