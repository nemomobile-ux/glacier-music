cmake_minimum_required(VERSION 3.6.0)

project(glacier-music
	VERSION 0.2.0
	DESCRIPTION "The Glacier music player")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)

include(FindPkgConfig)
include(FeatureSummary)
include(GNUInstallDirs)

set(QT_MIN_VERSION "6.0.0")
find_package(Qt6 COMPONENTS Core Gui Qml Quick Multimedia Sql DBus LinguistTools REQUIRED)
find_package(Glacier 0.9 COMPONENTS App REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(NEMONOTIFICATIONS nemonotifications-qt6 REQUIRED IMPORTED_TARGET)
pkg_check_modules(TAGLIB taglib REQUIRED IMPORTED_TARGET)
if(TAGLIB_FOUND)
	set_property(GLOBAL APPEND PROPERTY PACKAGES_FOUND taglib)
else()
	set_property(GLOBAL APPEND PROPERTY PACKAGES_NOT_FOUND taglib)
endif()

add_subdirectory(src)


install(DIRECTORY images
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/glacier-music)
install(FILES glacier-music.desktop
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

# Translations
file(GLOB TS_FILES translations/*.ts)
qt_add_translation(QM_FILES ${TS_FILES})
add_custom_target(translations DEPENDS ${QM_FILES})
add_dependencies(glacier-music translations)

install(FILES ${QM_FILES}
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/glacier-music/translations)
