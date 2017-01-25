cmake_minimum_required(VERSION 3.6)
project(CarGame)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Loader.cpp Loader.h Level.cpp Level.h car.cpp car.h circleobject.cpp circleobject.h exception.h Object.cpp Object.h polygonobject.cpp polygonobject.h rectangleobject.cpp rectangleobject.h)
add_executable(CarGame ${SOURCE_FILES})

set(CMAKE_BUILD_TYPE debug)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(CarGame ${SFML_LIBRARIES})
endif()

find_package(TinyXML QUIET)
if(TinyXML_FOUND)
    include_directories(${TinyXML_INCLUDE_DIRS})
    target_link_libraries(CarGame ${TinyXML_LIBRARIES})
endif()

target_link_libraries(CarGame Box2D)


