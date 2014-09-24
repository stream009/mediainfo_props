cmake_minimum_required(VERSION 3.0.2)
project(myplugin)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")

set(SRCS mediainfo_props.cpp)
 
kde4_add_plugin(mediainfo_props ${SRCS})
 
target_link_libraries(mediainfo_props
    ${KDE4_KIO_LIBS}
    dl
)
 
install(TARGETS mediainfo_props DESTINATION ${PLUGIN_INSTALL_DIR} )
install(FILES mediainfo_props.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
