#include <GL\glew.h>
#include <GL\freeglut.h>
#include <cmath>
#include "Particle.h"
#include "Scene.h"



int main(int argc, char** argv) {
    Scene(argc, argv);
    glutMainLoop();

    return 0;

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplFreeGLUT_Shutdown();
    ImGui::DestroyContext();
}