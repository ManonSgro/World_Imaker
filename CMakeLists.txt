cmake_minimum_required(VERSION 3.0)

project(ImacGL)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

#find_package(SDL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${SDL2_INCLUDE_DIRS})

# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} glimac/include third-party/include third-party/include/imgui)

add_subdirectory(glimac)
add_subdirectory(third-party/include/imgui)
#add_subdirectory(third-party/include/eigen)

#set(ALL_LIBRARIES glimac imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${EIGEN3_INCLUDE_DIR})
set(ALL_LIBRARIES glimac imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

file(GLOB TP_DIRECTORIES "WI*")

foreach(TP ${TP_DIRECTORIES})
    add_subdirectory(${TP})
endforeach()
