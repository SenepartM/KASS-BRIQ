#include <SFML/Graphics.hpp>
#include <deque>

class Brick {
public:
	Brick(int x, int y, int width, int height, int health); // Constructeur
	~Brick(); // Destructeur
	void draw(sf::RenderWindow& window); // Dessiner la brique sur la fenêtre
	bool isAlive(); // Renvoyer true si la brique est en vie, sinon false
	void destroyAndDelete(std::deque<Brick*>& bricks); // Supprimer la brique de la mémoire et de la deque
	void hit(); // Réduire la santé de la brique et changer sa couleur
	sf::Vector2f getPosition(); // Renvoyer la position de la brique
	sf::RectangleShape getShape(); // Renvoyer la forme de la brique
	sf::Vector2f getSize(); // Renvoyer la taille de la brique
	bool operator==(const Brick& other) const; // Comparer deux briques

private:
	sf::Vector2f position; // Position de la brique
	sf::Vector2f size; // Taille de la brique
	sf::RectangleShape shape; // Forme de la brique
	int health; // Santé de la brique
	float lastCollisionTime; // Temps de la dernière collision avec la balle
	sf::Clock clock; // Horloge pour mesurer le temps écoulé depuis la dernière collision
	void setColor(); // Changer la couleur de la brique en fonction de sa santé
};