CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(BomberPerson)

IF (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "No build type selected. Default to RELEASE")
    SET(CMAKE_BUILD_TYPE "RELEASE")
ENDIF()

# TODO: Check if USE_OPENNI has been set and set it for the compilation.

# TODO: Check compiler version to be at least g++4.7 or clang++3.1.

FIND_PACKAGE(SDL REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED) # TODO: Make this optional
FIND_PACKAGE(X11 REQUIRED) # OpenGL should already have taken care of this...
# TODO: Check for OpenNI
#TODO: OpenNI Stuff: ADD_DEFINITIONS(-I/usr/include/ni)
#TODO: OpenNI Stuff: ADD_DEFINITIONS(-Dlinux)

INCLUDE_DIRECTORIES(
   ${SDL_INCLUDE_DIR}
   ${OPENGL_INCLUDE_DIR}
   ${X11_INCLUDE_DIR}
)

FILE(GLOB BOMBERPERSON_SOURCES src/*.cpp
                               src/*/*.cpp)

ADD_DEFINITIONS(
   -Wall
   -std=c++11
)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

ADD_EXECUTABLE(BomberPerson ${BOMBERPERSON_SOURCES})

TARGET_LINK_LIBRARIES(
   ${PROJECT_NAME}
   ${SDL_LIBRARY}
   ${OPENGL_LIBRARIES}
   ${X11_LIBRARIES}
   SDL_image
   SDL_gfx
)
