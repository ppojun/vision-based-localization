cmake_minimum_required(VERSION 3.0)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(ProjName viewer)
PROJECT(${ProjName})


set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( Threads REQUIRED )
find_package( OpenCV REQUIRED )
find_package( glfw3 REQUIRED )
find_package( assimp REQUIRED )

message(STATUS "Found Assimp library in ${ASSIMP_LIBRARIES}")

message(STATUS "Found GLFW3 in ${GLFW_INCLUDE_DIRS}")
message(STATUS "Found GLFW3 in ${GLFW_LIBRARY}")

find_package( OpenGL REQUIRED )
message(STATUS "Found OPENGL in ${OPENGL_INCLUDE_DIR}")
message(STATUS "Found OPENGL in ${OPENGL_LIBRARY}")

find_package( glm REQUIRED )
message(STATUS "GLM included at ${GLM_INCLUDE_DIRS}")

set(imgui ../libs/imgui_190703)
set(gl3w ../libs/gl3w_190703)
set(stb ../libs/stb_190703)

#set(SyeCommon ../../SyeCommon)

INCLUDE_DIRECTORIES(
	${OPENGL_INCLUDE_DIR}
	${GLM_INCLUDE_DIRS}
	${stb}
	${gl3w}/include
	${imgui}
	${imgui}/examples
)

add_definitions("-Wall" "-g")

file(GLOB SOURCES 
	${gl3w}/src/gl3w.c
	${imgui}/*.cpp
	${imgui}/examples/imgui_impl_glfw.cpp
	${imgui}/examples/imgui_impl_opengl3.cpp
	./src/*
)

message("SOURCES. [${SOURCES}]")
ADD_EXECUTABLE(${ProjName} ${SOURCES})

if (APPLE)
	find_library(COCOA_LIBRARY Cocoa)
	find_library(OpenGL_LIBRARY OpenGL)
	find_library(IOKIT_LIBRARY IOKit)
	find_library(COREVIDEO_LIBRARY CoreVideo)
	
	SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} )

	find_library(
		assimp_LIBRARIES
		NAMES assimp
	)
	message("yyyy ${assimp_LIBRARIES}")

elseif (UNIX)
	if(${CMAKE_SYSTEM} MATCHES Linux)
		message("		opengl tutorial source share.cpp gl3w.h 변경 >>>>>>>>>>>>>>>>> LINUX")
		SET(EXTRA_LIBS GL ${ASSIMP_LIBRARIES})
    endif()
endif ()

if(assimp_FOUND)
	message(" assimp link path : [${ASSIMP_LIBRARY_DIRS}]")
	message("	Found ASSIMP Package. [${ASSIMP_LIBRARIES}]")
	message("	Found ASSIMP Package. [${assimp_LIBRARIES}]")
	message("	link_directories(${CMAKE_SOURCE_DIR}/lib)")
endif(assimp_FOUND)

link_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(
	${ProjName} 
	${CMAKE_THREAD_LIBS_INIT}
	${EXTRA_LIBS}
	${OpenCV_LIBS} 
	${assimp_LIBRARIES}
	pthread
	dl
	glfw
)
