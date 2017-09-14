import QtQuick 2.6

import QtQuick.Controls 1.0
import QtQuick.Controls.Nemo 1.0
import QtQuick.Controls.Styles.Nemo 1.0

Item{
    width: parent.width
    height: Theme.itemHeightHuge

    Image{
        id: coverImage
        source: cover
        width: parent.height
        height: parent.height
    }

    Label{
        text: artist+" - "+track
        width: parent.width-cover.width
        font{
            bold: true
            pixelSize: Theme.fontSizeExtraLarge
        }
        anchors{
            left: coverImage.right
            leftMargin: coverImage.height/2
        }

        verticalAlignment: Text.AlignVCenter
    }
}
