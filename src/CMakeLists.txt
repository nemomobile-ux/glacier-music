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

add_executable(glacier-music ${SRC})

target_link_libraries(glacier-music
	Qt5::Qml
	Qt5::Quick
	Qt5::Multimedia
	Qt5::Sql
	Glacier::App
	PkgConfig::TAGLIB)
install(TARGETS glacier-music RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY qml
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/glacier-music)
