#pragma once

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Brick.h"

class Ball
{
private:
	sf::CircleShape shape;
	sf::Vector2f oldPosition;
	sf::Vector2f position;
	float speed;
	int radius;
	sf::Vector2f direction;
	int lives;

	static bool isRandInitialized;
	double randomizeAngle();
	void setAngle(double angle);
public:
	Ball(int x, int y, int radius, float speed);
	~Ball();
	void move(float ellapsedTime);
	void draw(sf::RenderWindow& window);

	float getSpeed() const;
	void setSpeed(float newSpeed);

	void setPosition(sf::Vector2f newPosition);
	sf::Vector2f getPosition() const;
	void setDirection(sf::Vector2f newDirection);
	int getLives() const;
	void manageCollisionWithWindow(const sf::RenderWindow& window);
	void manageCollisionWithPlatform(Platform& platform);
	void manageCollisionWithBrick(Brick* brick);
};