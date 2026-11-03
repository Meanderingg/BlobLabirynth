cmake_minimum_required(VERSION 3.16)
project(BlobLabyrinth LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

# SOIL does not ship a CMake package, so locate the library directly.
find_library(SOIL_LIBRARY NAMES SOIL)
if(NOT SOIL_LIBRARY)
    message(FATAL_ERROR "SOIL library not found")
endif()

add_executable(labyrinth
    labyrinth.cpp
    SRC/imageloader.cpp
    SRC/loadShaders.cpp
)

target_include_directories(labyrinth PRIVATE INCLUDE)

# GLM_ENABLE_EXPERIMENTAL: labyrinth.cpp includes glm/gtx/transform.hpp.
target_compile_definitions(labyrinth PRIVATE
    GLM_ENABLE_EXPERIMENTAL
    ASSET_DIR="${CMAKE_SOURCE_DIR}"
)

target_link_libraries(labyrinth PRIVATE
    GLEW::GLEW
    GLUT::GLUT
    OpenGL::GL
    OpenGL::GLU
    glm::glm
    ${SOIL_LIBRARY}
)

set_target_properties(labyrinth PROPERTIES
    OUTPUT_NAME game.out
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
