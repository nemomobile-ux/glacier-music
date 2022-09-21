#include "fromtagscoverplugin.h"
#include <audiofile.h>

FromTagsCoverPlugin::FromTagsCoverPlugin()
{
}

void FromTagsCoverPlugin::getCover(Track* track)
{
    qDebug() << Q_FUNC_INFO;

    AudioFile file(track->getFileName());
    QImage coverImgFromTags = file.coverImg();
    if (!coverImgFromTags.isNull()) {
        m_coverImage = coverImgFromTags;
        emit coverChanged();
    } else {
        qDebug() << "Cover not found";
    }
}
