cmake_minimum_required(VERSION 3.16)

project(project-name LANGUAGES CXX)

include_directories(src)
include_directories(lib)
include_directories(include)

#Subdirectories allgemein
add_subdirectory(lib/freetype)
include_directories(lib/freetype/include)
add_subdirectory(lib/stb)
include_directories(lib/stb/include)

#Subdirectories Plattformabhängig
if(WIN32)
else()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

#Wenn Der Build im Debug-Modus ist
if(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
endif()

#Unterlibraries
add_library(PixelRenderer
	src/Color.cpp src/Font.cpp src/FontManager.cpp src/Geometry.cpp src/Renderer.cpp src/String32.cpp
	src/Texture.cpp src/TextureLoader.cpp src/TextureManager.cpp
)

list(APPEND libs
	stb
	freetype
)

#Externe Libraries
if (WIN32)
    set(CMAKE_BUILD_TYPE Release)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
else()
    set(CMAKE_CXX_FLAGS -no-pie)
endif()

#Hauptprogramm
target_link_libraries(PixelRenderer PRIVATE "${libs}")
add_executable(Program src/Test/Main.cpp)
set_target_properties(Program PROPERTIES OUTPUT_NAME "Voller Programmname")

if (WIN32)
    target_link_libraries(Program PRIVATE "${libs}")
	#target_link_libraries(PixelRenderer PRIVATE "${libs}")
	
	set_target_properties("${libs}" PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
else()
    target_link_libraries(Program PRIVATE PixelRenderer)
	
endif()
