#ifndef ARTIST_H
#define ARTIST_H

#include "item.h"
#include "dbadapter.h"

class Artist : public Item
{
    Q_OBJECT
public:
    Artist(QObject *parent = 0);

public slots:
    static Artist* toId(const int artistId);
    const QString getName() {return m_name;}
    void remove();
    void update();
    QList<Track*> getTracks();
    int insert();
    static int idFromName(const QString name);
    bool setName(const QString name);

private:
    QString m_name;
    QString m_oldname;
    int m_id;

    static QString getHash(const QString&);
    static QHash<int, Artist*> m_cache;

    int trackCount();
};

typedef QPointer<Artist> ArtistPointer;
Q_DECLARE_METATYPE(ArtistPointer)

#endif // ARTIST_H
