#ifndef TRACKSMODEL_H
#define TRACKSMODEL_H

#include <QAbstractListModel>
#include <track.h>

class TracksModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)

public:
    explicit TracksModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const { return m_hash; }

    Q_INVOKABLE void clearPlaylist();
    int currentIndex() { return m_currentIndex; }
    void setCurrentIndex(int index);

signals:
    void currentIndexChanged(int currentIndex);

public slots:
    void loadPlaylistFromDB();
    QVariant get(const int idx);

private:
    QHash<int, QByteArray> m_hash;
    QList<Track*> m_tracks;

    int m_currentIndex;
};

#endif // TRACKSMODEL_H
