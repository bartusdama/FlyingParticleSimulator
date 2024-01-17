#include "Scene.h"
#include "Particle.h"
#include <iostream>
#include <memory>
#include <vector>


std::vector<std::unique_ptr<Particle>> Particles_vec;

void addParticle(float centerX, float centerY)
{
    bool freePlace = true;
    float size = 0.1;
    for (const auto& particle : Particles_vec)
    {
        float distance = 
            std::sqrt((centerX - particle->fCenterX) * (centerX - particle->fCenterX) + (centerY - particle->fCenterY) * (centerY - particle->fCenterY));
        float sumOfRad = size + particle->fSize;
        if (distance <= sumOfRad)
        {
            freePlace = false;
            break;
        }
        else
            freePlace = true;
    }
    if (freePlace == true)
    {
        Triangle newCircle(centerX, centerY, 0.02f, 0.01f, size);
        Particles_vec.push_back(std::make_unique<Triangle>(newCircle));
    }
}

void addParticleWithMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float centerX = static_cast<float>(x) / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1; // zakres (0;1)*2 -1 -> (-1;1)
        float centerY = 1 - static_cast<float>(y) / glutGet(GLUT_WINDOW_HEIGHT) * 2; // odwraca i normalizuje zakres do (-1;1)
        addParticle(centerX, centerY);

        glutPostRedisplay();
    }
}

void init()
{
    glClearColor(0.0, 0.5, 0.5, 0.0);  // Czarny kolor tla
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Ustawienie ukladu wspolrzednych
}

static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void guiInteraction()
{
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use format strings too)

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))
    {
    }
        
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}


void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.8f, 0.1f);  // Zielony kolor
    for (const auto& particle : Particles_vec)
    {
        particle->Draw();
    }
    glFlush();

}

void updateScene(int value) {

    for (const auto& particle : Particles_vec)
    {
        particle->update(Particles_vec);
    }

    glutPostRedisplay();

    glutTimerFunc(16, updateScene, 0);
}

void display()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplFreeGLUT_NewFrame();

    guiInteraction();

    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();

    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    drawScene();

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}


void Scene(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Simulator");

    //init();

    ImGui::CreateContext();

    ImGui_ImplFreeGLUT_Init();
    ImGui_ImplFreeGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(16, updateScene, 0);
    glutMouseFunc(addParticleWithMouse);



    glutMainLoop();
}


