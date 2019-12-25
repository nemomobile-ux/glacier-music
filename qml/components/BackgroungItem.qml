import QtQuick 2.6
import QtGraphicalEffects 1.0

Item {
    id: backgroundItem

    Image {
        id: backCover
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop

        Connections{
            target: nextTrackModel
            onCurrentIndexChanged:{
                backgroundItem.changeBackground();
            }
        }
    }

    GaussianBlur {
        anchors.fill: backCover
        source: backCover
        samples: 25
        radius: 400
        deviation: 25
    }

    function changeBackground() {
        var currentItremCover = nextTrackModel.get(nextTrackModel.currentIndex).cover
        if(currentItremCover != "") {
            backCover.source = currentItremCover;
        } else {
            backCover.source =  "/usr/share/glacier-music/images/cover.png"
        }
    }
}
