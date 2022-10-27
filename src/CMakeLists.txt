set(SRC
    glaciermusicplayer.cpp
    glaciermusicplayer.h
    main.cpp)

qtquick_compiler_add_resources(RESOURCES qml/glacier-music.qrc)

add_subdirectory(lib)
add_subdirectory(qml/plugin)
add_subdirectory(plugins)

include_directories("lib")

add_executable(glacier-music ${SRC} ${RESOURCES})

target_link_libraries(glacier-music
    Qt5::Multimedia
    Glacier::App
    Glacier::Music)

install(TARGETS glacier-music RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR})
