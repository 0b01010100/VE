# The minmum version of cmake that is required in order to run this program
cmake_minimum_required(VERSION 3.15)
# Spefiy project name
project( "VE" )
# Define Unicode symbols
if(WIN32)
    add_definitions(-D_UNICODE -DUNICODE)
endif()
add_library(Games STATIC
    "Games/Game0/G/VGame0.cpp"
)
include_directories("${CMAKE_SOURCE_DIR}/Games/Game0")

# Include directories for engine header files
target_include_directories(Games PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Games")

add_subdirectory(Extensions)
# Add the executable target
add_executable(
    VE
    "VEmain.cpp"
)

# Link the libraries to the executables
target_link_libraries(VE PUBLIC Games)
target_link_libraries(Games PUBLIC Def)
target_link_libraries(VE PUBLIC Def)
