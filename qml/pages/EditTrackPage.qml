import QtQuick 2.6

import QtQuick.Controls 1.0 //needed for the Stack attached property
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0


import org.glacier.music.trackmodel 1.0

Page {
    id: libraryPage

    property int trackId

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Edit track info")
        showBackButton: true;
    }
}
