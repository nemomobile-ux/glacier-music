#ifndef ARTISTSQLMODEL_H
#define ARTISTSQLMODEL_H

#include <QSqlQueryModel>

class ArtistSqlModel :public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit ArtistSqlModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const { return hash; }

private:
    const static char* SQL_SELECT;
    QHash<int,QByteArray> hash;

public slots:
    void refresh();
    void searchQuery(const QString name);
    void cleanQuery();
};

#endif // ARTISTSQLMODEL_H
