cmake_minimum_required(VERSION 3.10)
project(OpenGLSetup LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Include FetchContent
include(FetchContent)

# Download GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# Download GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# Recursively search for all .cpp source files in the "src" directory
# and update the build if any of them change.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create the executable "OpenGLSetup" using the collected source files.
add_executable(OpenGLSetup ${SOURCES})

# Include directories
target_include_directories(OpenGLSetup PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc 
    ${glfw_SOURCE_DIR}/include 
    ${glad_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(OpenGLSetup PRIVATE glfw glad)
