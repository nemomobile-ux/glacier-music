import QtQuick
import QtMultimedia
//import QtGraphicalEffects

import Nemo.Controls

Item{
    id: coverArea
    property alias cover: coverImage.source
    clip: true

    Image{
        id: coverImage
        width: parent.width*0.8
        height: width
        source: "file:///usr/share/glacier-music/images/cover.png"
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: parent
    }
}
