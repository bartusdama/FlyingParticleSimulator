
#include "test.h"
#include "pch.h"
#include "../../../include/Particle.h"
#include "../../../include/Scene.h"

//sprawdzanie poprawności ruchu
TEST(ParticleTest, UpdateMovement)
{
    Circle particle(0.0f, 0.0f, 1.0f, 1.0f, 0.1f);

    // Zapisujemy początkowe położenie
    float initialX = particle.GetCenterX();
    float initialY = particle.GetCenterY();

    particle.update(std::vector<std::unique_ptr<Particle>>());

    // Sprawdzamy, czy położenie uległo zmianie zgodnie z prędkością
    EXPECT_NE(initialX, particle.GetCenterX());
    EXPECT_NE(initialY, particle.GetCenterY());
}

TEST(ParticleTest, AddParticleIncreasesVectorSize)
{
    std::vector<std::unique_ptr<Particle>> particles = {};

    int initalSize = particles.size();

    // Dodajemy nową cząstkę
    addParticle(0.0f, 0.0f, 0.1f);

    // Sprawdzamy, czy liczba cząsteczek zwiększyła się o 1
    EXPECT_EQ(initalSize + 1, particles.size());
}

TEST(ParticleTest, CollisionDetectionTrue)
{
    Circle particle1(0.0f, 0.0f, 0.1f, 0.0f, 0.05f);
    Circle particle2(0.1f, 0.0f, -0.1f, 0.0f, 0.05f);

    // Sprawdzamy, czy funkcja zwraca true dla kolidujących obiektów
    EXPECT_TRUE(particle1.checkCollision(particle2));
}