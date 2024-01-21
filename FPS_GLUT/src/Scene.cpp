#include "Scene.h"
#include "Particle.h"
#include <iostream>
#include <memory>
#include <vector>


std::vector<std::unique_ptr<Particle>> Particles_vec;

enum ParticleType {
    CIRCLE,
    SQUARE,
    HEXAGON,
    TRIANGLE
};
ParticleType selectedType;


void addParticle(float centerX, float centerY, float size)
{
    bool freePlace = true;
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
        std::unique_ptr<Particle> newParticle;
        switch (selectedType)
        {
        case CIRCLE:
            newParticle = std::make_unique<Circle>(centerX, centerY, 0.02f, 0.01f, size);
            break;
        case SQUARE:
            newParticle = std::make_unique<Square>(centerX, centerY, 0.02f, 0.01f, size);
            break;
        case HEXAGON:
            newParticle = std::make_unique<Hexagon>(centerX, centerY, 0.02f, 0.01f, size);
            break;
        case TRIANGLE:
            newParticle = std::make_unique<Triangle>(centerX, centerY, 0.02f, 0.01f, size);
            break;
        default:

            break;
        }
        Particles_vec.push_back(std::move(newParticle));
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Czarny kolor tla
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Ustawienie ukladu wspolrzednych
}

static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void guiInteraction()
{
    static float size = 0.0f;
    static int counter = -1;
    static float centerX = 0.0f;
    static float centerY = 0.0f;

    if (ImGui::Begin("Control Panel"))
    {
        ImGui::Text("Particle settings:");

        if (ImGui::CollapsingHeader("Select a particle type"))
        {
            if (ImGui::Button("Circle"))
            {
                selectedType = CIRCLE;
            }
            if (ImGui::Button("Hexagon"))
            {
                selectedType = HEXAGON;
            }
            if (ImGui::Button("Square"))
            {
                selectedType = SQUARE;
            }
            if (ImGui::Button("Triangle"))
            {
                selectedType = TRIANGLE;
            }

        }

        if (ImGui::CollapsingHeader("Set the particle size"))
        {
            ImGui::SliderFloat("Size:", &size, 0.0f, 0.5f);
        }

        if (ImGui::CollapsingHeader("Set the particle position (X, Y)"))
        {
            ImGui::SliderFloat("X:", &centerX, -0.5f, 0.5f);
            ImGui::SliderFloat("Y:", &centerY, -0.5f, 0.5f);
        }

        if (ImGui::Button("Add particle"))
        {
            addParticle(centerX, centerY, size);
        }

        if (ImGui::Button("Reset"))
        {
            Particles_vec.clear();
        }
        ImGui::SameLine();
        ImGui::Text("Remove all particles");

        if (ImGui::Button("Quit"))
        {
            exit(0);
        }

        ImGui::Text("Number of particles = %d", Particles_vec.size());

        if (ImGui::CollapsingHeader("Change the background color"))
        {
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
        }
    }
    ImGui::End();
}


void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (const auto& particle : Particles_vec)
    {
        glColor3f(particle->color.r, particle->color.g, particle->color.b);  // Zielony kolor
        particle->Draw();
    }
    glFlush();
}

void updateScene(int value) {

    for (auto it = Particles_vec.begin(); it != Particles_vec.end();)
    {
        auto& particle = *it;
        particle->update(Particles_vec);

        if (particle->timeToRemove())
        {
            it = Particles_vec.erase(it);
        }
        else 
        {
            ++it;
        }
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

    init();

    ImGui::CreateContext();

    ImGui_ImplFreeGLUT_Init();
    ImGui_ImplFreeGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(16, updateScene, 0);


    glutMainLoop();
}


