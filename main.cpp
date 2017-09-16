/*
 * Copyright (C) 2017 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif
#include <QtGui/QGuiApplication>


#include <QtQml>
#include <QtQuick/QQuickView>
#include <QtCore/QString>
#include <QScreen>
#include <QCoreApplication>

#include "src/collection.h"
#include "src/models/artistsqlmodel.h"

int main(int argc, char *argv[])
{
    setenv("QT_QUICK_CONTROLS_STYLE", "Nemo", 1);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("NemoMobile");
    app.setApplicationName("glacier-music");

    qmlRegisterType<Collection>("org.glacier.music.collection",1,0,"Collection");
    qmlRegisterType<ArtistSqlModel>("org.glacier.music.artistmodel",1,0,"ArtistModel");

    QQmlApplicationEngine* engine = new QQmlApplicationEngine(QUrl("/usr/share/glacier-music/qml/glacier-music.qml"));
    QObject *topLevel = engine->rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    engine->rootContext()->setContextProperty("__window", window);

    window->setTitle(QObject::tr("Music"));
    window->showFullScreen();
    return app.exec();
}
