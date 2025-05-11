cmake_minimum_required(VERSION 3.10)
project(VE LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Include FetchContent
include(FetchContent)

# Configure SDL2 options - MUST be set before FetchContent_MakeAvailable
option(SDL_SHARED "Build a SDL shared library" OFF)
option(SDL_STATIC "Build a SDL static library" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Download SDL2
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.28.5
)
FetchContent_MakeAvailable(SDL2)

# Fetch SDL_image with proper configuration
FetchContent_Declare(
  SDL2_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG release-2.6.3
)

# Configure SDL_image options
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE)
set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_DEPS_SHARED OFF CACHE BOOL "" FORCE)
# Match SDL2 build type - both must be static
set(SDL2IMAGE_SDL2_SHARED OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_SDL2_STATIC ON CACHE BOOL "" FORCE)
# Disable image formats you don't need to reduce dependencies
set(SDL2IMAGE_JPG ON CACHE BOOL "" FORCE)
set(SDL2IMAGE_PNG ON CACHE BOOL "" FORCE)
set(SDL2IMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_AVIF OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL2_image)

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
    ${SDL2_image_SOURCE_DIR}
)

# Copy the shader folder and its content into the bin folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Link libraries - use the static versions
target_link_libraries(VE PRIVATE 
    SDL2::SDL2
    SDL2_image
    glad 
    tinyobjloader
)