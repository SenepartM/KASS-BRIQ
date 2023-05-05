#include "Platform.h"

Platform::Platform(int y, int width, int height)
{
	this->y = y;
	this->size = sf::Vector2f(width, height);
	this->position = sf::Vector2f(350, y);
	this->shape = sf::RectangleShape(size);
	shape.setFillColor(sf::Color(sf::Color::Red));
}

Platform::~Platform()
{
}

void Platform::draw(sf::RenderWindow& window)
{
	shape.setPosition(position);
	window.draw(shape);
}

sf::Vector2f Platform::getPosition()
{
	return position;
}

sf::RectangleShape Platform::getShape()
{
	return shape;
}

sf::Vector2f Platform::getSize()
{
	return size;
}

void Platform::handleKeyboard(sf::Keyboard::Key key, bool isPressed)
{
	// on déplace la plateforme vers la gauche ou la droite en fonction de la touche enfoncée
	if (key == sf::Keyboard::Q)
	{
		velocity = isPressed ? -PLATFORM_SPEED : 200;
	}
	else if (key == sf::Keyboard::D)
	{
		velocity = isPressed ? PLATFORM_SPEED : 200;
	}
	else
	{
		velocity = 0;
	}
}

void Platform::update(float deltaTime)
{
	// on met à jour la position de la plateforme en fonction de la vitesse et du temps écoulé depuis la dernière mise à jour
	position.x += velocity * deltaTime;
	// on vérifie que la plateforme ne sort pas de l'écran
	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x + size.x > SCREEN_WIDTH)
	{
		position.x = SCREEN_WIDTH - size.x;
	}

	shape.setPosition(position);
}

void Platform::move(float distance)
{
	position.x += distance;
	// on vérifie que la plateforme ne sort pas de l'écran
	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x + size.x > SCREEN_WIDTH)
	{
		position.x = SCREEN_WIDTH - size.x;
	}

	shape.setPosition(position);
}
sf::Vector2f Platform::getSurfaceNormal(sf::Vector2f point)
{
	// Calcule la position relative du point par rapport à la plateforme
	sf::Vector2f relativePoint = point - position;
	relativePoint.x = std::max(-size.x / 2.0f, std::min(relativePoint.x, size.x / 2.0f));
	relativePoint.y = std::max(-size.y / 2.0f, std::min(relativePoint.y, size.y / 2.0f));

	// Calcule la normale de la surface de collision
	if (std::abs(relativePoint.x) > std::abs(relativePoint.y))
	{
		return sf::Vector2f(std::signbit(relativePoint.x) ? -1.0f : 1.0f, 0.0f);
	}
	else
	{
		return sf::Vector2f(0.0f, std::signbit(relativePoint.y) ? -1.0f : 1.0f);
	}
}
