cmake_minimum_required(VERSION 3.28.1)

set(PROJECT_NAME FPS_GLUT)

project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE Debug)

if(WIN32)
    set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /std:c++17 /Za /D_UNICODE /DUNICODE")
    set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1 /std:c++17 /Za /D_UNICODE /DUNICODE")
    message("Win settings chosen...")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall")
    message("Linux settings chosen...")
endif()


include_directories(include)


file(GLOB SOURCES "./src/*.cpp" "./include/*.h")
add_executable(${PROJECT_NAME} ${SOURCES} "src/Particle.cpp" "src/Scene.cpp")


find_package(GLEW REQUIRED)
find_package(FreeGLUT REQUIRED)


include_directories(${GLEW_INCLUDE_DIRS} ${FREEGLUT_INCLUDE_DIRS})


target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${FREEGLUT_LIBRARIES})


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")