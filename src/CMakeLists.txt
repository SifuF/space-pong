cmake_minimum_required(VERSION 3.22.1)

project(Pong VERSION 1.0)

#set(MAKE_BUILD_TYPE Debug ... FORCE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(GRAPHICS "Enable Graphics mode" ON)
configure_file(PongConfig.h.in PongConfig.h)

add_executable(Pong main.cpp)

if(WIN32)
set_target_properties(Pong PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
endif() 

target_include_directories(Pong PUBLIC
    "${PROJECT_BINARY_DIR}"
)

if(WIN32)
target_include_directories(Pong PUBLIC
    "${PROJECT_SOURCE_DIR}/SFML/include"
)

target_link_directories(Pong PUBLIC
    "${PROJECT_SOURCE_DIR}/SFML/lib"
)
endif() 

target_link_libraries(Pong PUBLIC
    optimized sfml-graphics
    optimized sfml-system
    optimized sfml-window
    optimized sfml-network
    optimized sfml-audio
)

if(WIN32)
target_link_libraries(Pong PUBLIC
    debug sfml-main-d optimized sfml-main
    debug sfml-graphics-d
    debug sfml-system-d
    debug sfml-window-d
    debug sfml-network-d
    debug sfml-audio-d
)
endif() 

file(COPY ${PROJECT_SOURCE_DIR}/sound/ DESTINATION ${PROJECT_BINARY_DIR}/sound/)
if(WIN32)
file(COPY ${PROJECT_SOURCE_DIR}/SFML/bin/ DESTINATION ${PROJECT_BINARY_DIR})
endif() 

#install(TARGETS Pong DESTINATION bin)
#install(DIRECTORY "${PROJECT_SOURCE_DIR}/sound/" DESTINATION bin/sound)
#if(WIN32)
#install(DIRECTORY "${PROJECT_SOURCE_DIR}/SFML/bin/" DESTINATION bin)
#endif()

