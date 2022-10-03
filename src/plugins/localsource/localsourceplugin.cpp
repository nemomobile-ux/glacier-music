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

    //    connect(collection, &Collection::rescanCollectionFinished, this, &LocalSourcePlugin::loadPlaylistFromDB);
    connect(m_tracksModel, &TracksModel::modelReset, this, &LocalSourcePlugin::calcButtonStatus);
    connect(m_tracksModel, &TracksModel::currentIndexChanged, this, &LocalSourcePlugin::makeTrackPlayed);
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

void LocalSourcePlugin::loadPlaylist(PlayMode mode, QString param)
{
    if (mode != PlayMode::Random) {
        qWarning() << "Support only random playlist now";
    }
    loadRandomPlayList();
}

void LocalSourcePlugin::clearPlaylist()
{
    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);
    if (query.exec("DELETE FROM playlist")) {
        m_tracksModel->reset();
    }
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

void LocalSourcePlugin::loadRandomPlayList()
{
    qDebug() << Q_FUNC_INFO;

    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    QString queryString = "SELECT tracks.fileName FROM playlist "
                          "INNER JOIN tracks ON playlist.song_id = tracks.id "
                          "WHERE time = 0 "
                          "ORDER by playlist.id ASC";

    bool ok = query.exec(queryString);
    if (!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    } else {
        while (query.next()) {
            Track* track = new Track(query.value(0).toString());
            if (track != nullptr) {
                m_tracksModel->addTrack(track);
            }
        }
    }
}

void LocalSourcePlugin::makeTrackPlayed(int id)
{
    Track* currentTrack = m_tracksModel->getTrack(id);
    QString currentTrackFileName = currentTrack->getFileName();

    QSqlDatabase db = dbAdapter::instance().getDatabase();
    QSqlQuery query(db);

    query.prepare("UPDATE playlist SET time = :time "
                  "WHERE time = 0 "
                  "AND song_id = (SELECT id FROM tracks WHERE fileName = '"
        + currentTrackFileName + "') "
                                 "ORDER BY id ASC "
                                 "LIMIT 1");
    query.bindValue(":time", QDateTime::currentMSecsSinceEpoch());
    bool ok = query.exec();
    if (!ok) {
        qDebug() << query.lastQuery() << query.lastError().text();
    }
}
