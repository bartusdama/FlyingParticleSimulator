cmake_minimum_required( VERSION 3.14 )

set( PROJECT_NAME FPS_Gtest )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )


if( WIN32 )
	set( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /std:c++17 /D_UNICODE /DUNICODE" )
	set( CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1 /std:c++17 /D_UNICODE /DUNICODE" )
	message( "Win settings chosen..." )
elseif( UNIX )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall" )
	message( "Linux settings chosen..." )
endif()




include_directories( include "../FPS_GLUT/include" )


file ( GLOB SOURCES "./src/*.cpp" "./include/*.h" )
add_executable(${PROJECT_NAME} ${SOURCES} "../FPS_GLUT/src/Particle.cpp" "../FPS_GLUT/src/Scene.cpp")

find_package(FreeGLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${FREEGLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} GTest::gtest_main ${FREEGLUT_LIBRARIES} ${GLEW_LIBRARIES})



# ---------------------------------------------------------
# Add GTest framework
# https://google.github.io/googletest/quickstart-cmake.html

include(FetchContent)
FetchContent_Declare(  	googletest
			DOWNLOAD_EXTRACT_TIMESTAMP YES
  			URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
		    )
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include( GoogleTest )
gtest_discover_tests( ${PROJECT_NAME} )
# ---------------------------------------------------------



# Set the default project 
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )


message( "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}" )