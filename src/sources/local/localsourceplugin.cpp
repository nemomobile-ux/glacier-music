#include "localsourceplugin.h"

LocalSourcePlugin::LocalSourcePlugin(QObject* parent)
{
}

bool LocalSourcePlugin::hasBack()
{
    return false;
}

void LocalSourcePlugin::setHasBack(bool hasBack)
{
}

bool LocalSourcePlugin::hasForward()
{
    return false;
}

void LocalSourcePlugin::setHasForward(bool hasForward)
{
}

QList<Track*> LocalSourcePlugin::tracks()
{
    QList<Track*> traks;

    return traks;
}

void LocalSourcePlugin::setTracks(QList<Track*> tracks)
{
}
