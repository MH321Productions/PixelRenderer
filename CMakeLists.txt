cmake_minimum_required(VERSION 3.2)

project(pixel-renderer LANGUAGES CXX)

option(PR_USE_SVG "Enable the rendering of svgs via lunasvg" OFF)

#Includes and Subdirectories
include_directories(lib)
include_directories(include)
add_subdirectory(lib/freetype)
include_directories(lib/freetype/include)
include_directories(lib/stb)

list(APPEND libs freetype)

if (PR_USE_SVG)
	add_subdirectory(lib/lunasvg)
	include_directories(lib/lunasvg/include)
	include_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/lunasvg/include)

	add_compile_definitions(PR_SVG)
	list(APPEND libs lunasvg)
endif()

set(CMAKE_CXX_STANDARD 17)

#Main Library
add_library(PixelRenderer STATIC
	src/Color.cpp src/Font.cpp src/FontManager.cpp src/Geometry.cpp src/Renderer.cpp src/String32.cpp
	src/Texture.cpp src/TextureLoader.cpp src/TextureManager.cpp src/stbImpl.cpp src/UTFLoader.cpp
)
target_link_libraries(PixelRenderer PRIVATE ${libs})

#Testing (only if option is activated)
option(PR_BUILD_TESTS "Builds the Rendering test programs" OFF)

if (PR_BUILD_TESTS)
	enable_testing()
	
	#Stb Save and Load Test
	add_executable(StbTest src/Test/stb/stbTest.cpp)
	set_target_properties(StbTest PROPERTIES OUTPUT_NAME "PixelRenderer stb Test")
	target_link_libraries(StbTest PRIVATE PixelRenderer)
	add_test(NAME StbTest COMMAND "PixelRenderer stb Test")
	#Animation Test (generating 10 second video)
	add_executable(AnimTest
		src/Test/Animation/AnimTest.cpp src/Test/Animation/Anim1Shapes.cpp
		src/Test/Animation/Anim2Textures.cpp src/Test/Animation/Anim3Blending.cpp
		src/Test/Animation/Anim4Repetition.cpp src/Test/Animation/Anim5Fonts.cpp
		src/Test/Animation/AnimFunctions.cpp src/Test/Animation/Anim6Sprite.cpp
	)
	set_target_properties(AnimTest PROPERTIES OUTPUT_NAME "PixelRenderer Animation Test")
	target_link_libraries(AnimTest PRIVATE PixelRenderer)
	add_test(NAME AnimTest COMMAND "PixelRenderer Animation Test")

endif()