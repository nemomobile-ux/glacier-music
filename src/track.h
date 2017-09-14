#ifndef TRACK_H
#define TRACK_H

#include <QtCore>
#include "item.h"

class Artist;

class Track : public Item
{
    Q_OBJECT
public:
    Track(QString file);

    Artist* getArtist() {return m_artist;}
    void setArtist(Artist *artist) {m_artist = artist;}

public slots:
    Q_INVOKABLE static Track* toId(int trackId);
    Q_INVOKABLE QString getTitle() {return m_title;}
    Q_INVOKABLE QString getAlbum() {return m_album;}
    Q_INVOKABLE QString getGenre() {return m_genre;}
    Q_INVOKABLE QString getComment() {return m_comment;}

    int getArtistId() {return m_artist_id;}
    int getNumber() {return m_number;}
    int getYear() {return m_year;}
    int getLength() {return m_length;}

    void setTitle(QString title) {m_title = title;}
    void setAlbum(QString album) {m_album = album;}
    void setGenre(QString genre) {m_genre = genre;}
    void setNum(int num) {m_number = num;}
    void setYear(int year) {m_year = year;}
    void setLength(int length) {m_length = length;}
    void setComment(QString comment) {m_comment = comment;}
    void setArtistId(int id);
    void setArtistName(QString name);

    int insert();
    void update();
    void remove();

signals:
    void titleChanged();
    void trackFileNotFound();

private:
    int m_id;

    int m_artist_id;
    QString m_title;
    QString m_album;
    QString m_genre;
    int m_number;
    int m_year;
    QString m_comment;
    QString m_fileName;
    int m_length;

    Artist *m_artist;
    QString m_artist_title;
    bool m_played;

    uint m_startTime;
    uint m_endTime;
};
#endif // TRACK_H
