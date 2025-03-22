cmake_minimum_required(VERSION 3.10)
project(VE LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

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

# Download tinyobjloader
FetchContent_Declare(
  tinyobjloader
  GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
  GIT_TAG v2.0.0rc10
)
FetchContent_MakeAvailable(tinyobjloader)

# Recursively search for all .cpp source files in the "src" directory
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS Engine/src/*.cpp Game/*.cpp)

# Create the executable "VE"
add_executable(VE ${SOURCES})

# Include directories
target_include_directories(VE PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/inc 
    ${SDL2_SOURCE_DIR}/include 
    ${glad_SOURCE_DIR}/include
    ${stb_SOURCE_DIR}
    ${tinyobjloader_SOURCE_DIR}
)

# Copy the shader folder and its content into the bin folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assests DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Link libraries
target_link_libraries(VE PRIVATE SDL2-static glad tinyobjloader)