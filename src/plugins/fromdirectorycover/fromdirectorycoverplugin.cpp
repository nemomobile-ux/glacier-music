#include "fromdirectorycoverplugin.h"

FromDirectoryCoverPlugin::FromDirectoryCoverPlugin()
{
}

void FromDirectoryCoverPlugin::getCover(Track* track)
{
    /*Search cover image in file folder*/
    QFileInfo musicFileInfo(track->getFileName());
    QString musicFileDir = musicFileInfo.absoluteDir().absolutePath();
    QFile localCover(musicFileDir + "/cover.jpg");
    if (localCover.exists()) {
        QImage coverImage = QImage(musicFileDir + "/cover.jpg");
        if (!coverImage.isNull()) {
            m_coverImage = coverImage;
            track->setCover(m_coverImage);
        }
    } else {
        qDebug() << "Cover not found";
    }
}
