SET(PLUGINNAME localsource)

SET(SRC ${PLUGINNAME}plugin.cpp)
SET(HEADERS ${PLUGINNAME}plugin.h)

set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_PLUGIN)

add_library(${PLUGINNAME} MODULE ${SRC} ${HEADERS})
include_directories("../../lib")

target_link_libraries(${PLUGINNAME} PUBLIC
    Qt5::Gui
    Qt5::Qml
    Qt5::DBus
    Glacier::Music)

install(TARGETS ${PLUGINNAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/glacier-music/plugin/sources)
