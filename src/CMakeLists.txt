set(SRC
	collection.cpp
	collection.h
	cover.cpp
	cover.h
	downloader.cpp
	downloader.h
	main.cpp
	musicbrainzconnect.cpp
	musicbrainzconnect.h
	rescancollection.cpp
	rescancollection.h)

qtquick_compiler_add_resources(RESOURCES qml/glacier-music.qrc)

add_subdirectory(lib)
add_subdirectory(plugin)
include_directories("lib")
add_executable(glacier-music ${SRC} ${RESOURCES})

target_link_libraries(glacier-music
	Qt5::Qml
	Qt5::Quick
	Qt5::Multimedia
        Qt5::DBus
	Glacier::App
        Glacier::Music
        PkgConfig::TAGLIB
        PkgConfig::NEMONOTIFICATIONS)
install(TARGETS glacier-music RUNTIME
	DESTINATION ${CMAKE_INSTALL_BINDIR})
