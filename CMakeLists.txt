cmake_minimum_required( VERSION 3.28.1 )

project( FPS_GLUT )


add_compile_options( -O3 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" )

add_executable(
	FPS_GLUT
	FPS_GLUT/src/main.cpp
	FPS_GLUT/src/Particle.cpp
	FPS_GLUT/src/Scene.cpp
)

#add_library(
#        imgui
#        imgui/imgui.cpp
#        imgui/imgui_demo.cpp
#        imgui/imgui_draw.cpp
#        imgui/imgui_widgets.cpp
#        imgui/examples/imgui_impl_opengl3.cpp
#        imgui/examples/imgui_impl_sdl.cpp
#)
#target_link_libraries(PhysicPhysics imgui)
#include_directories( imgui/ )
#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DIMGUI_IMPL_OPENGL_LOADER_GLEW" )


# opengl
find_package ( OpenGL REQUIRED )
if (OPENGL_FOUND )
    target_link_libraries ( FPS_GLUT ${OPENGL_LIBRARY} )
    target_link_libraries ( FPS_GLUT ${OPENGiL_gl_LIBRARY} )
    target_link_libraries ( FPS_GLUT ${OPENGL_glu_LIBRARY} )
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGL_SILENCE_DEPRECATION" )


set(GLEW_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/include/GL)
set(GLEW_LIBRARIES ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32/glew32.lib)

include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(FPS_GLUT ${GLEW_LIBRARIES})

# FreeGLUT Library
include_directories ( "include" "src" )

file ( GLOB SRC_FREEGLUTLIB "src/*.c" )


add_library ( freeglut ${SRC_FREEGLUTLIB} ${DEF_FILE} )

if ( CYGWIN OR MSYS OR MINGW OR MSVC )
  #ADD_DEFINITIONS(-mthreads -Wall -O2 -DNDEBUG -DWIN32 -D_MBCS -D_USRDLL -DFREEGLUT_EXPORTS)
  add_definitions ( -DWIN32 -DFREEGLUT_EXPORTS )
  target_link_libraries ( freeglut winmm user32 gdi32 ${OPENGL_LIBRARIES} )
elseif ( UNIX )
find_package ( X11 REQUIRED )
include_directories ( ${X11_INCLUDE_DIR} )
target_link_libraries ( freeglut ${OPENGL_LIBRARIES} ${X11_LIBRARIES} )
endif ( )