import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0


Page {
    id: libraryPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Library")
        showBackButton: true;
    }

    TabView {
        anchors.fill: parent

        style: touchStyle

        Tab {
            title: "Artists"
            ArtistsPage{visible: true}
        }
        Tab {
            title: "Tracks"
        }

        Component {
            id: touchStyle
            TabViewStyle {
                tabsAlignment: Qt.AlignVCenter
                tabOverlap: 0
                frame: Item { }
                tab: Item {
                    implicitWidth: control.width/control.count
                    implicitHeight: Theme.itemHeightMedium
                    BorderImage {
                        anchors.fill: parent
                        border.bottom: size.dp(8)
                        border.top: size.dp(8)

                        Text {
                            anchors.centerIn: parent
                            color: (styleData.selected) ? Theme.accentColor : Theme.textColor
                            text: styleData.title.toUpperCase()
                            font.pixelSize: Theme.fontSizeSmall
                        }
                        Rectangle {
                            visible: index > 0
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.margins: size.dp(10)
                            width:1
                            color: "#3a3a3a"
                        }
                        Rectangle{
                            visible: styleData.selected
                            width: parent.width
                            height: 1
                            color: Theme.accentColor
                            anchors{
                                bottom: parent.bottom
                            }
                        }
                    }
                }
            }
        }
    }
}
