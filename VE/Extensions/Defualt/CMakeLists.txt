add_library(Def STATIC 
	"VWindow/VWindow.cpp"
	"VGraphics/VGraphics.cpp"
	"VResourceChief/VResourceChief.cpp"
	"VInput/VInput.cpp"
)
add_subdirectory(VWindow)

target_include_directories(Def PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Def PUBLIC MS)

add_subdirectory(VGraphics)

target_include_directories(MSGE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Def PUBLIC MSGE)
target_link_libraries(MSGE PUBLIC MS)

add_subdirectory(VResourceChief)

target_include_directories(MSGE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Def PUBLIC MSR)

add_subdirectory(VInput)
target_include_directories(VInput PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Def PUBLIC VInput)