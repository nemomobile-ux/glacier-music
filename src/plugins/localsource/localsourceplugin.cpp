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

    connect(collection, &Collection::rescanCollectionFinished, this, &LocalSourcePlugin::loadPlaylistFromDB);
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

TracksModel* LocalSourcePlugin::tracksModel()
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

void LocalSourcePlugin::loadPlaylistFromDB()
{
    m_tracksModel->reset();
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    QString queryString = "SELECT filename FROM tracks \
                           ORDER BY RANDOM() \
                           LIMIT 10";

    bool ok = query.exec(queryString);
    if (!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    } else {
        while (query.next()) {
            Track* track = new Track(query.value(0).toString());
            m_tracksModel->addTrack(track);
        }
    }
}
