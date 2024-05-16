set(SRC artist.cpp
    audiofile.cpp
    coverpluginmanager.cpp
    downloader.cpp
    sourcepluginmanager.cpp
    track.cpp
    tracksmodel.cpp)

set(HEADERS coverpluginmanager.h
    sourcepluginmanager.h)

set(PUBLIC_HEADERS artist.h
    audiofile.h
    downloader.h
    coversourceplugin.h
    musicsourceplugin.h
    track.h
    tracksmodel.h)

add_library(glaciermusic SHARED ${SRC} ${HEADERS} ${PUBLIC_HEADERS})
add_library(Glacier::Music ALIAS glaciermusic)

target_link_libraries(glaciermusic
    Qt6::Core
    Qt6::Network
    Qt6::Gui
    PkgConfig::TAGLIB)

install(TARGETS glaciermusic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/)

install(FILES ${PUBLIC_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/glacier-music)
