TEMPLATE = app
TARGET = glacier-music

QT += qml quick sql multimedia

LIBS += -ltag

SOURCES += main.cpp \
    src/collection.cpp \
    src/dbadapter.cpp \
    src/rescancollection.cpp \
    src/audiofile.cpp \
    src/artist.cpp \
    src/track.cpp \
    src/models/artistsqlmodel.cpp \
    src/models/tracksqlmodel.cpp

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
    qml/pages/SettingsPage.qml \
    qml/components/CoverArea.qml \
    qml/components/PlaylistItem.qml \
    qml/pages/LibraryPage.qml \
    qml/pages/ArtistsPage.qml \
    qml/pages/TracksPage.qml

HEADERS += \
    src/collection.h \
    src/dbadapter.h \
    src/rescancollection.h \
    src/audiofile.h \
    src/item.h \
    src/artist.h \
    src/track.h \
    src/models/artistsqlmodel.h \
    src/models/tracksqlmodel.h
