set(SRC artist.cpp
    audiofile.cpp
    dbadapter.cpp
    track.cpp)

set(HEADERS item.h)

set(PUBLIC_HEADERS artist.h
    audiofile.h
    dbadapter.h
    track.h)

add_library(glaciermusic SHARED ${SRC} ${HEADERS} ${PUBLIC_HEADERS})
add_library(Glacier::Music ALIAS glaciermusic)

target_link_libraries(glaciermusic
    Qt5::Core
    Qt5::Gui
    Qt5::Sql)

install(TARGETS glaciermusic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/)

install(FILES ${PUBLIC_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/glacier-music)
