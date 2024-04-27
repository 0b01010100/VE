add_library(MS STATIC 
	"MSWindowManager/MSWinUser.cpp"
 )


target_include_directories(MS PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")