import QtQuick 2.6
import QtMultimedia 5.5
import QtGraphicalEffects 1.0

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

import org.glacier.music 1.0

Item{
    id: coverArea
    clip: true

    GlacierImage{
        id: coverImage
        width: parent.width*0.8
        height: width
        image: player.cover
        anchors.centerIn: parent
    }
}
