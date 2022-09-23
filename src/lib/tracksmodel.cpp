#include "tracksmodel.h"

TracksModel::TracksModel(QObject* parent)
    : m_currentIndex(-1)
{
    m_hash.insert(Qt::UserRole, QByteArray("artist"));
    m_hash.insert(Qt::UserRole + 1, QByteArray("title"));
    m_hash.insert(Qt::UserRole + 2, QByteArray("fileName"));
    m_hash.insert(Qt::UserRole + 3, QByteArray("album"));
    m_hash.insert(Qt::UserRole + 4, QByteArray("comment"));
    m_hash.insert(Qt::UserRole + 5, QByteArray("genre"));
    m_hash.insert(Qt::UserRole + 6, QByteArray("year"));
    m_hash.insert(Qt::UserRole + 7, QByteArray("length"));
    m_hash.insert(Qt::UserRole + 8, QByteArray("track"));
    m_hash.insert(Qt::UserRole + 9, QByteArray("cover"));
}

int TracksModel::rowCount(const QModelIndex& parent) const
{
    return m_tracks.count();
}

QVariant TracksModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= m_tracks.size()) {
        return QVariant();
    }

    Track* item = m_tracks.at(index.row());
    if (role == Qt::UserRole) {
        return item->artist();
    } else if (role == Qt::UserRole + 1) {
        return item->title();
    } else if (role == Qt::UserRole + 2) {
        return item->getFileName();
    } else if (role == Qt::UserRole + 3) {
        return item->album();
    } else if (role == Qt::UserRole + 4) {
        return item->comment();
    } else if (role == Qt::UserRole + 5) {
        return item->genre();
    } else if (role == Qt::UserRole + 6) {
        return item->year();
    } else if (role == Qt::UserRole + 7) {
        return item->length();
    } else if (role == Qt::UserRole + 8) {
        return item->title();
    } else if (role == Qt::UserRole + 9) {
        return item->cover();
    }

    return QVariant();
}

void TracksModel::clearPlaylist()
{
    beginResetModel();
    m_tracks.clear();
    m_currentIndex = -1;
    endResetModel();
}

void TracksModel::setCurrentIndex(int index)
{
    if (index != m_currentIndex) {
        m_currentIndex = index;
        emit currentIndexChanged(m_currentIndex);
    }
}

void TracksModel::loadPlaylistFromDB()
{
    beginResetModel();
    m_tracks.clear();
    m_currentIndex = -1;

    endResetModel();
}

void TracksModel::addTrack(Track* track)
{
    beginInsertRows(QModelIndex(), rowCount() - 1, rowCount());
    m_tracks.push_back(track);
    endInsertRows();
}

void TracksModel::reset()
{
    beginResetModel();
    m_tracks.clear();
    m_currentIndex = -1;
    endResetModel();
}

QVariant TracksModel::get(const int idx)
{
    if (idx >= m_tracks.size()) {
        return QVariant();
    }

    QMap<QString, QVariant> itemData;
    Track* item = m_tracks.at(idx);

    itemData.insert("artist", item->artist());
    itemData.insert("title", item->title());
    itemData.insert("fileName", item->getFileName());
    itemData.insert("album", item->album());
    itemData.insert("comment", item->comment());
    itemData.insert("genre", item->genre());
    itemData.insert("year", item->year());
    itemData.insert("length", item->length());
    itemData.insert("track", item->title());

    return QVariant(itemData);
}

Track* TracksModel::getTrack(const int idx)
{
    if (idx >= m_tracks.size() || idx < 0) {
        return nullptr;
    }

    return m_tracks.at(idx);
}
