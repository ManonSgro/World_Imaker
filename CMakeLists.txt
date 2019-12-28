cmake_minimum_required(VERSION 3.0)

project(World_Imaker)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

option(BUILD_DOC "Build documentation" ON)

#find_package(SDL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Doxygen REQUIRED)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/third-party/include/doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # the option ALL which allows to build the docs together with the application
    add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${DOXYGEN} glimac/include third-party/include third-party/include/imgui)

add_subdirectory(glimac)
add_subdirectory(third-party/include/imgui)

set(ALL_LIBRARIES glimac imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

#Build bin from src
add_subdirectory(src bin)
