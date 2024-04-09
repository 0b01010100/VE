# Add the library target
add_library(Libs STATIC 
	#defualt Libs
	"DefualtLibs/MSWindowManager/MSWinUser.cpp"
	"DefualtLibs/MSWindowManager/MSWinUser.h"
	"DefualtLibs/MSGraphicsManager/MSDX11User.cpp"
	"DefualtLibs/MSGraphicsManager/MSDX11User.hpp"
	"DefualtLibs/MSResourceManager/MSResUser.cpp"
	"DefualtLibs/MSResourceManager/MSResUser.h"
	"DefualtLibs/VDebug/VDebug.h"
)

# Include directories for header files
target_include_directories(Libs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
