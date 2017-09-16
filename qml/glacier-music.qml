import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0

import org.nemomobile.settings 1.0

import org.glacier.music.collection 1.0
import org.glacier.music.playlistmodel 1.0

import "pages"

ApplicationWindow {
    id: root

    property int cameraId: 0
    property string fileName: ""

    property var iso;

    Settings{
        id: settings;
    }

    Collection{
        id: collection
    }

    PlaylistModel{
        id: nextTrackModel
    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Back) {
            if (pageStack.depth > 1) {
                pageStack.pop();
                event.accepted = true;
            } else { Qt.quit(); }
        }
    }

    initialPage: PlayerPage{}

    Component.onCompleted: {
        if(collection.isFirstRun())
        {
            pageStack.push(Qt.resolvedUrl("/usr/share/glacier-music/qml/pages/SettingsPage.qml"));
        }

        nextTrackModel.formatAutoPlaylist()
    }

    Rectangle{
        id: rescanProgress
        width: parent.width
        height: Theme.itemHeightExtraSmall/10
        color: Theme.accentColor
        visible: false;
        anchors.top: root.top
    }

    Connections{
        target: collection
        onUpdateRescanProgress: {
            if(prc < 100)
            {
                rescanProgress.width = root.width*(prc/100);
                rescanProgress.visible = true;
            }
            else
            {
                rescanProgress.visible = false;
            }
        }
    }
}
