# Add the library target
add_library(Libs STATIC 
	#defualt Libs
	"DefualtLibs/MSWindowManager/MSWinUser.cpp"
	"DefualtLibs/MSGraphicsManager/MSDX11User.cpp"
	"DefualtLibs/MSGraphicsManager/MSDX11User.hpp"
	"DefualtLibs/MSResourceManager/MSResUser.cpp"
)

# Include directories for header files
target_include_directories(Libs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
