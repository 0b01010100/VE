add_library(MSR STATIC 
	"MSResourceManager/MSResUser.cpp"
)


target_include_directories(MSR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")