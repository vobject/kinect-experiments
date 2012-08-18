cmake_minimum_required(VERSION 2.8)

project(bomberperson)

add_definitions(-D__GXX_EXPERIMENTAL_CXX0X__)
add_definitions(-Dlinux)
add_definitions(-I/usr/include/SDL)
add_definitions(-I/usr/include/ni)
add_definitions(-O0)
add_definitions(-g3)
add_definitions(-Wall)
add_definitions(-std=c++11)

#add_subdirectory(src)

file(GLOB bomberperson_SOURCES src/*.cpp src/*/*.cpp)


#add_subdirectory(game)
#add_subdirectory(input)
#add_subdirectory(nui)
#add_subdirectory(render)
#add_subdirectory(utils)

add_executable(bomberperson ${bomberperson_SOURCES})

target_link_libraries (bomberperson SDL SDL_ttf GL OpenNI X11)
