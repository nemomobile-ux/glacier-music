import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0


Page {
    id: settingsPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Plugins")
        showBackButton: true;
    }

}
