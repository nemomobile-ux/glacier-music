### Sets QT_INSTALL_QML to the directory where QML Plugins should be installed
function(FindQtInstallQml)
    find_program(QMAKE NAMES qmake6 qmake)
    if(NOT QMAKE)
    message(FATAL_ERROR "qmake not found")
    endif()
    execute_process(
        COMMAND ${QMAKE} -query QT_INSTALL_QML
        OUTPUT_VARIABLE PROC_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(QT_INSTALL_QML ${PROC_RESULT} PARENT_SCOPE)
endfunction()

set(SRC
    plugin.cpp
    artistsqlmodel.cpp
    artistsqlmodel.h
    blurredimage.cpp
    blurredimage.h
    peakscreator.cpp
    peakscreator.h
    playlistmodel.cpp
    playlistmodel.h
    tracksqlmodel.cpp
    tracksqlmodel.h
    wavewidget.cpp
    wavewidget.h)

add_library(glaciermusicplugin SHARED ${SRC})
include_directories("../lib")

target_link_libraries(glaciermusicplugin
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Multimedia
    Qt6::Sql
    Glacier::Music)

FindQtInstallQml()

install(FILES qmldir DESTINATION ${QT_INSTALL_QML}/org/glacier/music/)
install(TARGETS glaciermusicplugin DESTINATION ${QT_INSTALL_QML}/org/glacier/music/)
