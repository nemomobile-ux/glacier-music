SET(PLUGINNAME localsource)

SET(SRC ${PLUGINNAME}plugin.cpp
        collection.cpp
        dbadapter.cpp
        rescancollection.cpp)

SET(HEADERS ${PLUGINNAME}plugin.h
        collection.h
        dbadapter.h
        rescancollection.h)

set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_PLUGIN)

add_library(${PLUGINNAME} MODULE ${SRC} ${HEADERS})
include_directories("../../lib")

target_link_libraries(${PLUGINNAME} PUBLIC
    Qt6::DBus
    Qt6::Sql
    Glacier::Music
    PkgConfig::NEMONOTIFICATIONS)

install(TARGETS ${PLUGINNAME}
    LIBRARY DESTINATION /usr/lib/glacier-music/plugin/sources)
