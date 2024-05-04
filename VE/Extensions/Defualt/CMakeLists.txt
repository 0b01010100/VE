add_library(Def STATIC 
	"VWindow/VWindow.cpp"
	"VGraphics/VGraphics.cpp"
	"VInput/VInput.cpp"
	"VMath/VMath.cpp"
	
)
add_subdirectory(VWindow)

target_include_directories(Def PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Def PUBLIC VWindow)

add_subdirectory(VGraphics)

target_include_directories(VGraphics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Def PUBLIC VGraphics)

add_subdirectory(VInput)
target_include_directories(VInput PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Def PUBLIC VInput)

add_subdirectory(VMath)
target_include_directories(VMath PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(Def PUBLIC VMath)

