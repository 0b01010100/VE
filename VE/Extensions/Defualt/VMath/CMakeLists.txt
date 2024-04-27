add_library(VMath STATIC 
	"VMath.h"
	"VMath.cpp"
)


target_include_directories(VMath PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")