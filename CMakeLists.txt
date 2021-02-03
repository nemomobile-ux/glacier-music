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

set(QT_MIN_VERSION "5.6.0")
find_package(Qt5 COMPONENTS Qml Quick Multimedia Sql REQUIRED)
find_package(Glacier COMPONENTS App REQUIRED)
find_package(PkgConfig REQUIRED)

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
