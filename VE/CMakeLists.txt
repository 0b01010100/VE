# The minmum version of cmake that is required in order to run this program
cmake_minimum_required(VERSION 3.15)
# Spefiy project name
project( "VE" )
# Define Unicode symbols
if(WIN32)
    add_definitions(-D_UNICODE -DUNICODE)
endif()
# Add engine source files
add_library(
    Engine STATIC
    "Engine/Window/VWindow.cpp"
    "Engine/Graphics/VGraphics.cpp"
    "Engine/ResourceChief/VResourceChief.cpp"
)
add_library(Games STATIC
    "Games/Game0/G/VGame0.cpp"
)
# Include directories for engine header files
target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Engine")
target_include_directories(Games PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Games")

# Add subdirectory for libraries in the Libs folder
add_subdirectory("Libs")
# Add the executable target
add_executable(
    VE
    "VEmain.cpp"
)

#if plaform is window include DX11 library
#if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    #message("Oh yea Platform is Windows")
    #target_link_libraries(VE PRIVATE d3d11)
#endif()
# Link the libraries to the executable
target_link_libraries(VE PRIVATE Engine)
target_link_libraries(VE PRIVATE Games)
target_link_libraries(VE PRIVATE Libs)
# Link the Libs library agisnt the Engine library
target_link_libraries(Engine PRIVATE Libs)
target_link_libraries(Games PRIVATE Libs)
target_link_libraries(Games PRIVATE Engine)