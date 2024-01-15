#pragma once

#include <vector>
#include <memory>

class Particle
{
public:
	float fSpeedX;
	float fSpeedY;
	float fSize;
	float fCenterX;
	float fCenterY;

public:
	float GetCenterX(void) const { return fCenterX; };
	float GetCenterY(void) const { return fCenterY; };
	void SetCenterX(float CenterX) { fCenterX = CenterX; };
	void SetCenterY(float CenterY) { fCenterY = CenterY; };
	void update(const std::vector<std::unique_ptr<Particle>>& Particles);
	bool checkCollision(const Particle& otherParticle) const;
	virtual void Draw();
	Particle(float centerX, float centerY, float speedX, float speedY, float size)
		: fCenterX(centerX), fCenterY(centerY), fSpeedX(speedX), fSpeedY(speedY), fSize(size) {}
};

class Circle : public Particle
{
private:
	const int fTriNumb = 50;

public:
	using Particle::Particle;
	void Draw() override;

};

class Hexagon : public Circle // to jest okrag oszczegolnej liczbie trojkotow
{
private:
	const int fTriNumb = 6;

public:
	void Draw() override;
	using Circle::Circle;
};

class Square : public Particle
{
private:
	

public:
	using Particle::Particle;
	void Draw() override;

};
