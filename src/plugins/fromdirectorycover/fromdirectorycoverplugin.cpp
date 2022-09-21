#include "fromdirectorycoverplugin.h"

FromDirectoryCoverPlugin::FromDirectoryCoverPlugin()
{
}

void FromDirectoryCoverPlugin::getCover(Track* track)
{
    qDebug() << Q_FUNC_INFO;
    /*Search cover image in file folder*/
    QFileInfo musicFileInfo(track->getFileName());
    QString musicFileDir = musicFileInfo.absoluteDir().absolutePath();
    QFile localCover(musicFileDir + "/cover.jpg");
    if (localCover.exists()) {
        QImage coverImage = QImage(musicFileDir + "/cover.jpg");
        if (!coverImage.isNull()) {
            m_coverImage = coverImage;
            emit coverChanged();
        }
    } else {
        qDebug() << "Cover not found";
    }
}
