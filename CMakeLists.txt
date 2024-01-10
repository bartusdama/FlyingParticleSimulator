cmake_minimum_required( VERSION 3.6.2 )

# For a new project it is sufficient to change only its name in the following line
set( PROJECT_NAME FPS_GLUT )

project( ${PROJECT_NAME} )


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


include_directories(${OPENGL_INCLUDE_DIRS} ${SOURCE_DIR}/Dependencies/freeglut/include ${SOURCE_DIR}/Dependencies/GLEW/include)
link_libraries(${OPENGL_INCLUDE_LIBS} ${SOURCE_DIR}/Dependencies/freeglut/lib ${SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32)

set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )

if( WIN32 )
	set( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /std:c++17 /Za /D_UNICODE /DUNICODE" )
	set( CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1 /std:c++17 /Za /D_UNICODE /DUNICODE" )
	message( "Win settings chosen..." )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall" )
	message( "Mac settings chosen..." )
elseif( UNIX )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall" )
	message( "Linux settings chosen..." )
endif()



# Inform CMake where the header files are
include_directories( FPS_GLUT/include )


# Automatically add all *.cpp and *.h files to the project
file ( GLOB SOURCES "./FPS_GLUT/src/*.cpp" "./FPS_GLUT/include/*.h" )
add_executable( ${PROJECT_NAME} ${SOURCES} )


# Set the default project 
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )


message( "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}" )
