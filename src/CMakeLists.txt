set(SRC
	artist.cpp
	artist.h
	audiofile.cpp
	audiofile.h
	collection.cpp
	collection.h
	cover.cpp
	cover.h
	dbadapter.cpp
	dbadapter.h
	downloader.cpp
	downloader.h
	item.h
	main.cpp
	musicbrainzconnect.cpp
	musicbrainzconnect.h
        peakscreator.cpp
        peakscreator.h
	rescancollection.cpp
	rescancollection.h
	track.cpp
	track.h
	models/artistsqlmodel.cpp
	models/artistsqlmodel.h
	models/playlistmodel.cpp
	models/playlistmodel.h
	models/tracksqlmodel.cpp
        models/tracksqlmodel.h
        widgets/blurredimage.cpp
        widgets/blurredimage.h
        widgets/wavewidget.cpp
        widgets/wavewidget.h)

qtquick_compiler_add_resources(RESOURCES qml/glacier-music.qrc)

add_executable(glacier-music ${SRC} ${RESOURCES})

target_link_libraries(glacier-music
	Qt5::Qml
	Qt5::Quick
	Qt5::Multimedia
	Qt5::Sql
        Qt5::DBus
	Glacier::App
        PkgConfig::TAGLIB
        PkgConfig::NEMONOTIFICATIONS)
install(TARGETS glacier-music RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
