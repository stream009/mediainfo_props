cmake_minimum_required(VERSION 3.3)
project(mediainfo_props)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

set(KDE_INSTALL_USE_QT_SYS_PATHS On)
include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(FeatureSummary)

find_package(Qt5 REQUIRED COMPONENTS Gui)
find_package(KF5 REQUIRED COMPONENTS KIO I18n)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")
endif()

kde_enable_exceptions()

set(SRCS mediainfo_props.cpp)

add_library(mediainfo_props MODULE ${SRCS})

target_link_libraries(mediainfo_props
    dl
    KF5::KIOWidgets
    KF5::I18n
    Qt5::Gui
)

install(TARGETS mediainfo_props DESTINATION ${PLUGIN_INSTALL_DIR} )
install(FILES mediainfo_props.desktop DESTINATION ${SERVICES_INSTALL_DIR} )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
