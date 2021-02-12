#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class PlayListModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)

    struct playListItem{
        int trackId;
        QString artist;
        int artist_id;
        QString title;
        QString fileName;
        bool played;
        QString cover;
    };

public:

    explicit PlayListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {return hash;}

    bool insertRows(int position, int rows, playListItem &item, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

public slots:
    void clearPlaylist();
    void loadPlaylistFromDB();
    void formatAutoPlaylist();
    void formatRandomPlaylist(const int tracksCount);
    void addItem(const int trackId, int count = 0);
    void setPlayed(const int idx, const QModelIndex &index = QModelIndex());
    QVariant get(const int idx);
    void remove(const int idx);
    void setCurrentIndex(int currentIndex);
    int currentIndex() {return m_currentIndex;}

signals:
    void playListUpdate();
    void currentIndexChanged(int currentIndex);

private:
    QHash<int,QByteArray> hash;
    QList<playListItem> playList;

    int m_currentIndex;
};

#endif // PLAYLISTMODEL_H
