#pragma once
#include "imgui.h"
#include "imgui_impl_freeglut.h"
#include "imgui_impl_opengl2.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif

void init();

void drawScene();

void updateScene(int value);

void Scene(int argc, char** argv);

void guiInteraction();

void addParticle(float centerX, float centerY, float size);