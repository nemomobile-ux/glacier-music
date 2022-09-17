#include "localsourceplugin.h"
#include "collection.h"

#include <QDebug>

LocalSourcePlugin::LocalSourcePlugin(QObject* parent)
    : m_tracksModel(nullptr)
    , m_hasBack(false)
    , m_hasForward(false)
{
    m_tracksModel = new TracksModel();

    Collection* collection = new Collection();
    collection->rescanCollection();

    connect(collection, &Collection::rescanCollectionFinished, m_tracksModel, &TracksModel::loadPlaylistFromDB);
    connect(m_tracksModel, &TracksModel::modelReset, this, &LocalSourcePlugin::calcButtonStatus);
}

bool LocalSourcePlugin::hasBack()
{
    return m_hasBack;
}

void LocalSourcePlugin::setHasBack(bool hasBack)
{
}

bool LocalSourcePlugin::hasForward()
{
    return m_hasForward;
}

void LocalSourcePlugin::setHasForward(bool hasForward)
{
}

QAbstractListModel* LocalSourcePlugin::tracksModel()
{
    return m_tracksModel;
}

void LocalSourcePlugin::calcButtonStatus()
{
    bool hasBack = m_tracksModel->currentIndex() > 0;
    bool hasForward = m_tracksModel->currentIndex() < m_tracksModel->rowCount();

    if (hasBack != m_hasBack) {
        m_hasBack = hasBack;
        emit hasBackChanged();
    }

    if (hasForward != m_hasForward) {
        m_hasForward = hasForward;
        emit hasForwardChanged();
    }
}
