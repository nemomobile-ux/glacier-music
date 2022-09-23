#include "fromtagscoverplugin.h"
#include <audiofile.h>

FromTagsCoverPlugin::FromTagsCoverPlugin()
{
}

void FromTagsCoverPlugin::getCover(Track* track)
{
    AudioFile file(track->getFileName());
    QImage coverImgFromTags = file.coverImg();
    if (!coverImgFromTags.isNull()) {
        m_coverImage = coverImgFromTags;
        track->setCover(m_coverImage);
    } else {
        qDebug() << "Cover not found";
    }
}
