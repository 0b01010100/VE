# Add the library target
add_library(Libs STATIC 
	#defualt Libs
	"DefualtLibs/MSWindowManager/MSWinUser.cpp"
	"DefualtLibs/VDebug/VDebug.h"
	
 "DefualtLibs/MSGraphicsManager/MSDX11User.h" "DefualtLibs/MSGraphicsManager/MSDX11User.cpp")

# Include directories for header files
target_include_directories(Libs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
