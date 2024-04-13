add_library(MSGE STATIC
	"MSGraphicsManager/MSDX11User.cpp"
)

target_include_directories(MSGE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

