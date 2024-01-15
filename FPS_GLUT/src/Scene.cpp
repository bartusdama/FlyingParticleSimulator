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
        Circle newCircle(centerX, centerY, 0.02f, 0.01f, size);
        Particles_vec.push_back(std::make_unique<Circle>(newCircle));
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
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Czarny kolor tla
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Ustawienie ukladu wspolrzednych
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.8f, 0.1f);  // Zielony kolor

    for (const auto& particle : Particles_vec)
        particle->Draw();

    glFlush();
}

void updateScene(int value) {
    
    for (const auto& particle : Particles_vec)
    {
        particle->update(Particles_vec);
    }

    glutPostRedisplay();

    // Ustaw ponownie timer
    glutTimerFunc(16, updateScene, 0);
}

void Scene(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Simulator");
    init();
    glutTimerFunc(16, updateScene, 0);
    glutDisplayFunc(display);
    glutMouseFunc(addParticleWithMouse);
}