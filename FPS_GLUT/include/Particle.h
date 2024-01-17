#pragma once
#include <cmath>
#define M_PI 3.14159265358979323846
#include <vector>
#include <memory>
#include <iostream>
#include <set>

class Particle
{
public:
	float fSpeedX;
	float fSpeedY;
	float fSize;
	float fMass = {};
	float fDensity = {};
	float fCenterX;
	float fCenterY;
	std::set<std::pair<const Particle*, const Particle*>> collidedPairs;

public:
	float GetCenterX(void) const { return fCenterX; };
	float GetCenterY(void) const { return fCenterY; };
	void SetCenterX(float CenterX) { fCenterX = CenterX; };
	void SetCenterY(float CenterY) { fCenterY = CenterY; };
	virtual float getMass() const { return fMass; }
	virtual float getDensity() const { return fDensity; }


	virtual void Draw() = 0;

	virtual ~Particle() = default;

	void update(const std::vector<std::unique_ptr<Particle>>& Particles);
	bool checkCollision(const Particle& otherParticle) const;

	
	Particle(float centerX, float centerY, float speedX, float speedY, float size)
		: fCenterX(centerX), fCenterY(centerY), fSpeedX(speedX), fSpeedY(speedY), fSize(size) {}
};


class Circle final : public Particle
{
public:
	float fDensity;
	float fMass;
	const int fTriNumb = 50;

public:
	Circle(float centerX, float centerY, float speedX, float speedY, float size)
		: Particle(centerX, centerY, speedX, speedY, size), fDensity(1.0f), fMass(fDensity* size* size* M_PI) {}

	void Draw() override;

	float getMass() const override { return fMass; }
	float getDensity() const override { return fDensity; }
};


class Triangle final : public Particle
{
public:
	float fDensity;
	float fMass;

public:
	Triangle(float centerX, float centerY, float speedX, float speedY, float size)
		: Particle(centerX, centerY, speedX, speedY, size), fDensity(4.f), fMass(fDensity * 2 * size * size) {}

	void Draw() override;

	float getMass() const override { return fMass; }
	float getDensity() const override { return fDensity; }
};


class Hexagon final : public Particle
{
public:
	float fDensity;
	float fMass;
	const int fTriNumb = 6;

public:
	Hexagon(float centerX, float centerY, float speedX, float speedY, float size)
		: Particle(centerX, centerY, speedX, speedY, size), fDensity(2.0f), fMass(fDensity* (3 * size * size * std::sqrt(3)) / 2) {};

	void Draw() override;

	float getMass() const override { return fMass; }
	float getDensity() const override { return fDensity; }
};


class Square final : public Particle
{
public:
	float fDensity;
	float fMass;

public:
	Square(float centerX, float centerY, float speedX, float speedY, float size)
		: Particle(centerX, centerY, speedX, speedY, size), fDensity(3.0f), fMass(fDensity* size* size) {};

	void Draw() override;

	float getMass() const override { return fMass; }
	float getDensity() const override { return fDensity; }
};
