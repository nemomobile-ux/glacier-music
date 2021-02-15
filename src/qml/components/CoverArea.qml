import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

Rectangle{
    id: coverArea
    width: parent.width
    height: width

    property alias cover: coverImage.source
    color: "transparent"
    clip: true

    Image{
        id: coverImage
        width: parent.width
        height: parent.height
        source: "/usr/share/glacier-music/images/cover.png"
        fillMode: Image.PreserveAspectFit
    }
}
