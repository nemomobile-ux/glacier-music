#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

class PlayListModel: public QAbstractListModel
{
    Q_OBJECT
    struct playListItem{
        int trackId;
        QString artist;
        QString title;
        QString fileName;
        bool played;
    };

public:
    explicit PlayListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {return hash;}

    bool insertRows(int position, int rows, playListItem &item, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

public slots:
    void formatAutoPlaylist();
    void addItem(const int trackId, int count = 0);
    void setPlayed(const int idx, const QModelIndex &index = QModelIndex());
    QVariant get(const int idx);
    void remove(const int idx);

signals:
    void playListUpdate();

private:
    QHash<int,QByteArray> hash;
    QList<playListItem> playList;

};

#endif // PLAYLISTMODEL_H
