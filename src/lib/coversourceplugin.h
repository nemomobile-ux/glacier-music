#ifndef COVERSOURCEPLUGIN_H
#define COVERSOURCEPLUGIN_H

#include "glaciermusic_global.h"
#include <QObject>

class GLACIERMUSIC_EXPORT CoverSourcePlugin : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString cover READ cover NOTIFY coverChanged)

public:
    virtual bool enabled() = 0;
    virtual QString name() = 0;

    virtual QString cover() = 0;
    virtual void getCover(QVariant data) = 0;

signals:
    void coverChanged();
};

Q_DECLARE_INTERFACE(CoverSourcePlugin, "GlacierMusic.CoverPlugin")
#endif // COVERSOURCEPLUGIN_H
