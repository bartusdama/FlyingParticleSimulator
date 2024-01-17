#include "Particle.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

void Particle::update(const std::vector<std::unique_ptr<Particle>>& Particles)
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
    for (const auto& otherParticle : Particles)
    {
        auto particlePair = std::minmax(this, otherParticle.get());

        if (otherParticle.get() != this && checkCollision(*otherParticle) &&
            collidedPairs.find(std::make_pair(this, otherParticle.get())) == collidedPairs.end())
        {
            float distance = std::sqrt(std::pow(fCenterX - otherParticle->fCenterX, 2) + std::pow(fCenterY - otherParticle->fCenterY, 2));
            float sumRadii = fSize + otherParticle->fSize;

            if (distance < sumRadii) {
                // Obliczanie wektorów jednostkowych między środkami obiektów
                float dx = otherParticle->fCenterX - fCenterX;
                float dy = otherParticle->fCenterY - fCenterY;
                float distanceNorm = std::sqrt(dx * dx + dy * dy);

                if (distanceNorm > 0) {
                    float nx = dx / distanceNorm;
                    float ny = dy / distanceNorm;

                    // Obliczanie prędkości względnej
                    float relativeVelocityX = otherParticle->fSpeedX - fSpeedX;
                    float relativeVelocityY = otherParticle->fSpeedY - fSpeedY;

                    // Obliczanie iloczynu skalarnego prędkości względnej i wektora normalnego
                    float dotProduct = relativeVelocityX * nx + relativeVelocityY * ny;

                    // Obliczanie współczynnika impulsu
                    float impulseCoeff = (2.0 * dotProduct) / (getMass() + otherParticle->getMass());

                    // Aktualizacja prędkości obiektów po zderzeniu
                    fSpeedX += impulseCoeff * otherParticle->getMass() * nx;
                    fSpeedY += impulseCoeff * otherParticle->getMass() * ny;
                    otherParticle->fSpeedX -= impulseCoeff * getMass() * nx;
                    otherParticle->fSpeedY -= impulseCoeff * getMass() * ny;

                    collidedPairs.insert(std::make_pair(this, otherParticle.get()));
                }
            }
            //else if()
        }
    }
    collidedPairs.clear();
}

bool Particle::checkCollision(const Particle& otherParticle) const
{
    float distance =
        std::sqrt((fCenterX - otherParticle.fCenterX) * (fCenterX - otherParticle.fCenterX) + (fCenterY - otherParticle.fCenterY) * (fCenterY - otherParticle.fCenterY));
    float sumOfRad = fSize + otherParticle.fSize;
    return distance < sumOfRad;
}

void Circle::Draw()
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

void Hexagon::Draw()
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

void Square::Draw()
{
    glBegin(GL_QUADS);
    glVertex2f(fCenterX - fSize, fCenterY - fSize);
    glVertex2f(fCenterX + fSize, fCenterY - fSize);
    glVertex2f(fCenterX + fSize, fCenterY + fSize);
    glVertex2f(fCenterX - fSize, fCenterY + fSize);
    glEnd();
}

void Triangle::Draw()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(fCenterX, fCenterY + fSize);
    glVertex2f(fCenterX + fSize, fCenterY - fSize);
    glVertex2f(fCenterX - fSize, fCenterY - fSize);
    glEnd();
}
