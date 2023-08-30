import QtQuick
import Nemo.Controls

Page {
    id: settingsPage

    headerTools: HeaderToolsLayout {
        id: tools
        title: qsTr("Settings")
        showBackButton: true;
    }

    Column {
        id: fileSortingRow
        width: parent.width
        anchors{
            top: parent.top
            topMargin: Theme.itemSpacingLarge
        }

        ListModel{
            id: fileOrganizeModel
            ListElement { name: qsTr("Only in interal storage") }
            ListElement { name: qsTr("Yes") }
            ListElement { name: qsTr("No") }
        }

        GlacierRoller {
            id: fileOrganize
            width: parent.width

            clip: true
            model: fileOrganizeModel
            label: qsTr("Enable file sorting")
            delegate: GlacierRollerItem {
                Text {
                    height: fileOrganize.itemHeight
                    text: name
                    color: Theme.textColor
                    font.pixelSize: Theme.fontSizeMedium
                    font.bold: (fileOrganize.activated && fileOrganize.currentIndex === index)
                }
            }
            onCurrentIndexChanged:{
                settings.setValue("sorting",fileOrganizeModel.get(fileOrganize.currentIndex).name);
            }
        }
    }

    Column{
        id: alwaysFromTheBeginningRow
        width: parent.width
        anchors{
            top: fileSortingRow.bottom
            margins: Theme.itemSpacingLarge
        }

        CheckBox {
            text:  qsTr("Always play from the beginning")
            anchors {
                left: parent.left
                leftMargin: height
            }
            checked: settings.value("alwaysFromTheBeginning",1) === 1
            onClicked: {
                if(checked) {
                    settings.setValue("alwaysFromTheBeginning",1)
                } else {
                    settings.setValue("alwaysFromTheBeginning",0)
                }
                console.warn(settings.value("alwaysFromTheBeginning",1))
            }
        }
    }
}
