cmake_minimum_required(VERSION 3.10)
project(OpenGLSetup LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Include FetchContent
include(FetchContent)

# Download SDL2
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.28.5
)
FetchContent_MakeAvailable(SDL2)

# Download GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# Download stb (contains stb_image.h)
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# Recursively search for all .cpp source files in the "src" directory
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create the executable "OpenGLSetup"
add_executable(OpenGLSetup ${SOURCES})

# Include directories
target_include_directories(OpenGLSetup PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc 
    ${SDL2_SOURCE_DIR}/include 
    ${glad_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
)

# Copy the shader folder and its content into the bin folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Textures DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Link libraries
target_link_libraries(OpenGLSetup PRIVATE SDL2-static glad)