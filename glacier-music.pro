TEMPLATE = app
TARGET = glacier-music

QT += qml quick sql

SOURCES += main.cpp \
    src/collection.cpp \
    src/dbadapter.cpp \
    src/rescancollection.cpp

target.path = /usr/bin

qml.files = qml/*
qml.path = /usr/share/glacier-music/qml

images.files = images/*
images.path = /usr/share/glacier-music/images/

desktop.files = glacier-music.desktop
desktop.path = /usr/share/applications

INSTALLS += target desktop qml images

DISTFILES += \
    rpm/glacier-music.spec \
    glacier-music.desktop \
    qml/glacier-music.qml \
    qml/pages/PlayerPage.qml \
    qml/pages/SettingsPage.qml

HEADERS += \
    src/collection.h \
    src/dbadapter.h \
    src/rescancollection.h
