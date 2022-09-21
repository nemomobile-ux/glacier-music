SET(PLUGINNAME fromtagscover)

SET(SRC ${PLUGINNAME}plugin.cpp)

SET(HEADERS ${PLUGINNAME}plugin.h)

set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_PLUGIN)

add_library(${PLUGINNAME} MODULE ${SRC} ${HEADERS})
include_directories("../../lib")

target_link_libraries(${PLUGINNAME} PUBLIC
    Glacier::Music)

install(TARGETS ${PLUGINNAME}
    LIBRARY DESTINATION /usr/lib/glacier-music/plugin/cover)
