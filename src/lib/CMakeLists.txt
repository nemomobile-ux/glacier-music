set(SRC artist.cpp
    audiofile.cpp
    downloader.cpp
    sourcepluginmanager.cpp
    track.cpp)

set(HEADERS sourcepluginmanager.h)

set(PUBLIC_HEADERS artist.h
    audiofile.h
    downloader.h
    coversourceplugin.h
    musicsourceplugin.h
    track.h)

add_library(glaciermusic SHARED ${SRC} ${HEADERS} ${PUBLIC_HEADERS})
add_library(Glacier::Music ALIAS glaciermusic)

target_link_libraries(glaciermusic
    Qt5::Core
    Qt5::Network
    Qt5::Gui
    PkgConfig::TAGLIB)

install(TARGETS glaciermusic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/)

install(FILES ${PUBLIC_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/glacier-music)
