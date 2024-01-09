#include "Scene.h"
#include "Particle.h"
#include <iostream>

Circle c1(0.0, 0.0, 0.02, 0.01, 0.1);
Square c2(0.0, 0.2, 0.02, 0.01, 0.1);

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Czarny kolor tla
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Ustawienie ukladu wspolrzednych
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.8f, 0.1f);  // Zielony kolor
    
    c1.DrawCircle();
    c2.DrawSquare();


    glFlush();
}

void updateScene(int value) {
    
    c1.update(c2);
    c2.update(c1);

    // Rysuj okrag zaktualizowany o nowy kat
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
}