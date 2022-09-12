import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

Item{
    id: coverArea
    property alias cover: coverImage.source
    clip: true

    Image{
        id: coverImage
        width: parent.width*0.8
        height: width
        source: "file://"+player.cover
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: parent
    }
}
