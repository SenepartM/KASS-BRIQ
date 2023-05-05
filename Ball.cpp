#include "Ball.h"

#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>


Ball::Ball(int x, int y, int radius, float speed) :
	position(x, y),
	oldPosition(position),
	direction(1.f, 1.f),
	radius(radius),
	speed(speed),
	lives(lives)
{
	shape.setFillColor(sf::Color::White);
	shape.setRadius(radius);
	setAngle(randomizeAngle());
}

Ball::~Ball()
{
}

double Ball::randomizeAngle()
{
	static bool isRandInitialized = false;
	if (!isRandInitialized)
	{
		srand(time(NULL));
		isRandInitialized = true;
	}

	return (((double)rand() / (double)RAND_MAX) * 60.0) - 30.0;
}

void Ball::setAngle(double angle)
{
	direction.x = sin(angle);
	direction.y = -cos(angle);
}

void Ball::move(float elapsedTime)
{
	oldPosition = position;
	position += elapsedTime * speed * direction;
	shape.setPosition(position);
}

void Ball::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

float Ball::getSpeed() const
{
	return speed;
}

void Ball::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Ball::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	oldPosition = position;
	shape.setPosition(position);
}

sf::Vector2f Ball::getPosition() const
{
	return position;
}

void Ball::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}
int Ball::getLives() const
{
	return lives;
}

void Ball::manageCollisionWithWindow(const sf::RenderWindow& window)
{
	// Si la balle sort de l'écran (par en haut)
	if (position.y <= 0)
	{
		// Inverse la direction sur l'axe y :
		direction.y *= -1;
		position.y = 0;
	}
	else if (position.y + 2 * radius >= window.getSize().y)
	{
		direction.y *= -1;
		position.y = window.getSize().y - 2 * radius;
	}

	if (position.x <= 0)
	{
		direction.x *= -1;
		position.x = 0;
	}
	else if (position.x + 2 * radius >= window.getSize().x)
	{
		direction.x *= -1;
		position.x = window.getSize().x - 2 * radius;

	}
}
void Ball::manageCollisionWithPlatform(Platform& platform)
{
	sf::FloatRect ballBounds = shape.getGlobalBounds();
	sf::FloatRect platformBounds = platform.getShape().getGlobalBounds();
	// Vérifie si la balle touche la plateforme
	if (ballBounds.intersects(platformBounds))
	{
		// Calcule la position relative de la balle par rapport à la plateforme
		double relativeIntersectX = position.x + radius - platform.getPosition().x - platform.getSize().x / 2.0;

		// Normalise la position relative de la balle
		double normalizedRelativeIntersectionX = relativeIntersectX / (platform.getSize().x / 2.0);

		// Calcule l'angle de rebond de la balle en radians
		double maxAngle = 45.0; // Angle de rebond maximum en degrés
		double angle = normalizedRelativeIntersectionX * maxAngle * M_PI / 180.0;

		// Change la direction de la balle en fonction de l'angle de rebond
		setAngle(angle);

		// Déplace la balle en dehors de la plateforme
		double overlap = ballBounds.top + ballBounds.height - platformBounds.top;
		position.y -= overlap;
		direction.y = -std::abs(direction.y);
	}
}

void Ball::manageCollisionWithBrick(Brick* brick)
{
	sf::FloatRect ballBounds = shape.getGlobalBounds();
	sf::FloatRect brickBounds = brick->getShape().getGlobalBounds();
	// Vérifie si la balle touche la brique
	if (ballBounds.intersects(brickBounds))
	{
		// Calcule la position relative de la balle par rapport à la brique
		double intersectX = position.x + radius - brick->getPosition().x;
		double intersectY = position.y + radius - brick->getPosition().y;
		double deltaX = brick->getSize().x / 2.0 - std::abs(intersectX);
		double deltaY = brick->getSize().y / 2.0 - std::abs(intersectY);

		// Inverse la direction de la balle en fonction de l'axe de la collision
		if (deltaX > deltaY)
		{
			// Collision horizontale
			direction.x *= -1;
		}
		else
		{
			// Collision verticale
			direction.y *= -1;
		}

		// Réduit la santé de la brique et change sa couleur
		brick->hit();

		// Changer la direction de la balle immédiatement après la collision
		// en fonction de la position de la brique relative à la balle
		if (intersectX > 0)
		{
			// La balle touche la brique sur le côté droit
			direction.x = std::abs(direction.x);
		}
		else
		{
			// La balle touche la brique sur le côté gauche
			direction.x = -std::abs(direction.x);
		}

		if (intersectY > 0)
		{
			// La balle touche la brique en bas
			direction.y = std::abs(direction.y);
		}
		else
		{
			// La balle touche la brique en haut
			direction.y = -std::abs(direction.y);
		}
	}
}
