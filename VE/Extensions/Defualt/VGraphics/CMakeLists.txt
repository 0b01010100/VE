add_library(MSGE STATIC
	"MSGraphicsManager/MSDX11.cpp"
	"VGraphicsResourceChief.cpp"
	"VGraphics.cpp"
)

target_include_directories(MSGE PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

