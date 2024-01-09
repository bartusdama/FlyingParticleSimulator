#include "Particle.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <cmath>

void Particle::update(const Particle& otherParticle)
{
    fCenterX += fSpeedX;
    fCenterY += fSpeedY;

    // Sprawdz kolizje z lewa krawedzia
    if (fCenterX - fSize < -1.0) {
        fCenterX = -1.0 + fSize;
        fSpeedX = -fSpeedX;  // Zmien kierunek ruchu
    }

    // Sprawdz kolizje z prawa krawedzia
    if (fCenterX + fSize > 1.0) {
        fCenterX = 1.0 - fSize;
        fSpeedX = -fSpeedX;  // Zmien kierunek ruchu
    }

    // Sprawdz kolizje z dolna krawedzia
    if (fCenterY - fSize < -1.0) {
        fCenterY = -1.0 + fSize;
        fSpeedY = -fSpeedY;  // Zmien kierunek ruchu
    }

    // Sprawdz kolizje z gorna krawedzia
    if (fCenterY + fSize > 1.0) {
        fCenterY = 1.0 - fSize;
        fSpeedY = -fSpeedY;
    }
    if (checkCollision(otherParticle))
    {
        fSpeedX = -fSpeedX;
        fSpeedY = fSpeedX;
    }
}

bool Particle::checkCollision(const Particle& otherParticle) const
{
    float distance = 
        std::sqrt((fCenterX - otherParticle.fCenterX) * (fCenterX - otherParticle.fCenterX) + (fCenterY - otherParticle.fCenterY) * (fCenterY - otherParticle.fCenterY));
    float sumOfRad = fSize + otherParticle.fSize;
    return distance < sumOfRad;
}

void Circle::DrawCircle()
{
    glBegin(GL_TRIANGLE_FAN);

    // Srodek okregu
    glVertex2f(fCenterX, fCenterY);

    // Przyblizanie okregu za pomoca trojkatow
    for (int i = 0; i <= fTriNumb; ++i) {
        float currentAngle = 2.0 * acos(-1.0) * i / fTriNumb;
        float x = fCenterX + 0.1 * cos(currentAngle);
        float y = fCenterY + 0.1 * sin(currentAngle);
        glVertex2f(x, y);
    }

    glEnd();
}

void Hexagon::DrawCircle()
{
    glBegin(GL_TRIANGLE_FAN);

    // Srodek okregu
    glVertex2f(fCenterX, fCenterY);

    // Przyblizanie okregu za pomoca trojkatow
    for (int i = 0; i <= fTriNumb; ++i) {
        float currentAngle = 2.0 * acos(-1.0) * i / fTriNumb;
        float x = fCenterX + 0.1 * cos(currentAngle);
        float y = fCenterY + 0.1 * sin(currentAngle);
        glVertex2f(x, y);
    }

    glEnd();
}

void Square::DrawSquare()
{
    glBegin(GL_QUADS);
    glVertex2f(fCenterX - fSize, fCenterY - fSize);
    glVertex2f(fCenterX + fSize, fCenterY - fSize);
    glVertex2f(fCenterX + fSize, fCenterY + fSize);
    glVertex2f(fCenterX - fSize, fCenterY + fSize);
    glEnd();
}
