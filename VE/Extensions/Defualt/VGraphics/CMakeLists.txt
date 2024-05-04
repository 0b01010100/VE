if(WIN32)
    set(DX11 "DX/11/DX11.cpp")
endif()

add_library(VGraphics STATIC
	"${DX11}"
	"VGraphicsResourceChief.cpp"
	"VGraphics.cpp"
)

target_include_directories(VGraphics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

