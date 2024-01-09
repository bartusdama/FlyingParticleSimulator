#pragma once

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
	void update(const Particle& otherParticle);
	bool checkCollision(const Particle& otherParticle) const;
	Particle(float centerX, float centerY, float speedX, float speedY, float size)
		: fCenterX(centerX), fCenterY(centerY), fSpeedX(speedX), fSpeedY(speedY), fSize(size) {}
};

class Circle : public Particle
{
private:
	const int fTriNumb = 50;

public:
	using Particle::Particle;
	void DrawCircle();

};

class Hexagon : public Circle // to jest okrag oszczegolnej liczbie trojkotow
{
private:
	const int fTriNumb = 6;

public:
	void DrawCircle();
	using Circle::Circle;
};

class Square : public Particle
{
private:
	

public:
	using Particle::Particle;
	void DrawSquare();

};
