cmake_minimum_required(VERSION 3.2)

project(pixel-renderer LANGUAGES CXX)

#Includes and Subdirectories
include_directories(lib)
include_directories(include)
add_subdirectory(lib/freetype)
include_directories(lib/freetype/include)
include_directories(lib/stb)

set(CMAKE_CXX_STANDARD 11)

#Main Library
add_library(PixelRenderer
	src/Color.cpp src/Font.cpp src/FontManager.cpp src/Geometry.cpp src/Renderer.cpp src/String32.cpp
	src/Texture.cpp src/TextureLoader.cpp src/TextureManager.cpp src/stbImpl.cpp
)
list(APPEND libs freetype)
target_link_libraries(PixelRenderer PRIVATE "${libs}")

#Testing
enable_testing()
add_executable(AnimTest src/Test/Main.cpp)
set_target_properties(AnimTest PROPERTIES OUTPUT_NAME "PixelRenderer Animation Test")
target_link_libraries(AnimTest PRIVATE PixelRenderer)
add_test(NAME AnimTest COMMAND "PixelRenderer Animation Test")