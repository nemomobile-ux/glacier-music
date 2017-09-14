#ifndef ITEM
#define ITEM

#include <QtCore>

class Track;

class Item : public QObject{
    Q_OBJECT

public:
    Item(QObject *parent = 0) : QObject(parent), id(0) {}
    int getId() const {return id;}
    void setId(int id) {this->id = id;}
    //virtual QString getName() = 0;

protected:
    int id;
};
typedef QPointer<Item> ItemPointer;
Q_DECLARE_METATYPE(ItemPointer)
#endif // ITEM
