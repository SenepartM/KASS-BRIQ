#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Vector2f size;
	int y;
	float velocity = 0.f; // ICI GERER LA VITRESSE DE LA PLATFORM

public:
	static constexpr float PLATFORM_SPEED = 300.f;
	static constexpr int SCREEN_WIDTH = 800;

	Platform(int y, int width, int height);
	~Platform();

	void draw(sf::RenderWindow& window);
	void handleKeyboard(sf::Keyboard::Key key, bool isPressed);
	void update(float deltaTime);
	void move(float distance);

	sf::Vector2f getSurfaceNormal(sf::Vector2f point);

	sf::RectangleShape getShape();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
};