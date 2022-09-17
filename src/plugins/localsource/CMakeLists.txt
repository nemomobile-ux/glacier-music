SET(PLUGINNAME localsource)

SET(SRC ${PLUGINNAME}plugin.cpp
        collection.cpp
        dbadapter.cpp
        rescancollection.cpp
        tracksmodel.cpp)
SET(HEADERS ${PLUGINNAME}plugin.h
        collection.h
        dbadapter.h
        rescancollection.h
        tracksmodel.h)

set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_PLUGIN)

add_library(${PLUGINNAME} MODULE ${SRC} ${HEADERS})
include_directories("../../lib")

target_link_libraries(${PLUGINNAME} PUBLIC
    Qt5::DBus
    Qt5::Sql
    Glacier::Music
    PkgConfig::NEMONOTIFICATIONS)

install(TARGETS ${PLUGINNAME}
    LIBRARY DESTINATION /usr/lib/glacier-music/plugin/sources)
