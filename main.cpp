#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>
// Fonction pour mapper une valeur d'une plage à une autre
double mapValue(double value, double min, double max, double nMin, double nMax)
{
	double newVal = (((value - min) / (max - min)) * (nMax - nMin)) + nMin;
	return newVal;
}

// Fonction pour afficher le menu et attendre que l'utilisateur appuie sur Espace pour lancer la partie
void showEnd(sf::RenderWindow& window) {
	// Chargement de la police de caractères par défaut
	sf::Font font;
	if (!font.loadFromFile("Fonts/bradybun.ttf"))
	{
		std::cout << "Erreur lors du chargement de la police" << std::endl;
		return;
	}

	// Définition du texte à afficher dans le menu
	sf::Text title;
	title.setFont(font);
	title.setString("KASS-BRIQ");
	title.setCharacterSize(80);
	title.setFillColor(sf::Color::White);
	title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 100);
	sf::Text lose;
	lose.setFont(font);
	lose.setString("VOUS AVEZ PERDU..");
	lose.setCharacterSize(60);
	lose.setFillColor(sf::Color::Green);
	lose.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 200);

	sf::Text startText;
	startText.setFont(font);
	startText.setString("Appuyez sur ENTRER pour quitter");
	startText.setCharacterSize(40);
	startText.setFillColor(sf::Color::Red);
	startText.setPosition(window.getSize().x / 2 - startText.getLocalBounds().width / 2, 300);

	// Boucle pour afficher le menu tant que l'utilisateur n'appuie pas sur Espace ou Entrée
	bool menuActive = true;
	while (menuActive)
	{
		// Gestion des événements de la fenêtre
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				menuActive = false;
				return;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
			{
				window.close();
				return;
			}
		}

		// Effacement de la fenêtre avant le dessin
		window.clear();

		// Dessin du titre et du texte pour lancer la partie
		window.draw(title);
		window.draw(lose);
		window.draw(startText);

		// Affichage des dessins dans la fenêtre
		window.display();
	}
}


void showMenu(sf::RenderWindow& window)
{
	// Chargement de la police de caractères par défaut
	sf::Font font;
	if (!font.loadFromFile("Fonts/bradybun.ttf"))
	{
		std::cout << "Erreur lors du chargement de la police" << std::endl;
		return;
	}



	// Définition du texte à afficher dans le menu
	sf::Text title;
	title.setFont(font);
	title.setString("KASS-BRIQ");
	title.setCharacterSize(80);
	title.setFillColor(sf::Color::White);
	title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 100);

	sf::Text startText;
	startText.setFont(font);
	startText.setString("Appuyez sur Espace pour commencer");
	startText.setCharacterSize(40);
	startText.setFillColor(sf::Color::Red);
	startText.setPosition(window.getSize().x / 2 - startText.getLocalBounds().width / 2, 300);

	// Boucle pour afficher le menu tant que l'utilisateur n'appuie pas sur Espace
	bool menuActive = true;
	while (menuActive)
	{
		// Gestion des événements de la fenêtre
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				menuActive = false;
				return;
			}
		}

		// Effacement de la fenêtre avant le dessin
		window.clear();

		// Dessin du titre et du texte pour lancer la partie
		window.draw(title);
		window.draw(startText);

		// Affichage des dessins dans la fenêtre
		window.display();
	}
}


int main()
{

	// Création de la plateforme, de la balle, des bricks et de la fenêtre
	std::deque<Brick*> bricks;
	Platform platform(550, 100, 11);
	Ball ball(200, 250, 10, 550); // x,y,size,speedddd


	sf::RenderWindow window(sf::VideoMode(800, 600), "KASS-BRIQ");
	showMenu(window);


	int numBricksPerLine = 10; // Nombre de briques par ligne
	int brickWidth = 80; // Largeur d'une brique
	int brickHeight = 30; // Hauteur d'une brique
	int horizontalSpacing = (800 - numBricksPerLine * brickWidth) / (numBricksPerLine + 1); // Espacement horizontal entre les briques
	int verticalSpacing = 30; // Espacement vertical entre les briques
	for (int i = 0; i < 4; i++) { // Boucle pour créer 4 lignes de bricks
		for (int j = 0; j < numBricksPerLine; j++) { // Boucle pour créer le nombre de briques spécifié par ligne
			int x = horizontalSpacing + j * (brickWidth + horizontalSpacing); // Position x de la brick en fonction de j
			int y = verticalSpacing + i * (brickHeight + verticalSpacing); // Position y de la brick en fonction de i
			bricks.push_back(new Brick(x, y, brickWidth, brickHeight, 3)); // Création d'une nouvelle brick et ajout dans la deque
		}
	}




	// Définition du rectangle qui sera utilisé pour dessiner la fenêtre
	sf::RectangleShape windowRect;
	windowRect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	// Variables pour le temps, la position de la souris, le temps écoulé et la position Y à ne pas dépasser par la balle par rapport à la plateforme
	sf::Clock clock;
	sf::Vector2i mousePos;
	float elapsedTime = 0, maxBallPosY = 550.f;
	sf::Font font;
	if (!font.loadFromFile("Fonts/bradybun.ttf"))
	{
		std::cout << "Erreur lors du chargement de la police" << std::endl;
		return 0;
	}
	sf::Text lifeText;
	lifeText.setFont(font);
	lifeText.setCharacterSize(20);
	lifeText.setFillColor(sf::Color::White);
	int life = 10;
	// Boucle principale pour maintenir la fenêtre ouverte
	while (window.isOpen())
	{
		lifeText.setString("Vie : " + std::to_string(life)); // où 'life' est la variable contenant la valeur de la vie
		lifeText.setPosition(10, 5); // ajustez la position du texte à votre guise
		window.draw(lifeText);
		// Calcul du temps écoulé depuis la dernière itération de la boucle
		elapsedTime = clock.restart().asSeconds();

		// Gestion des événements de la fenêtre
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Fermeture de la fenêtre si l'utilisateur le demande
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Vérifiez si la balle a atteint le bas de l'écran
	 // Vérifier si la balle a touché le bas de l'écran
		bool ballAtBottom = false;
		// Définir la ligne de départ pour la balle
		float ballStartLine = 250.f;

		// Générer une position aléatoire horizontale pour la balle
		float ballStartX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (600 - 10);

		// Définir la position de départ de la balle
		sf::Vector2f startingBallPosition(ballStartX, ballStartLine);



		if (life > 0) {
			if (ball.getPosition().y > maxBallPosY)
			{
				if (!ballAtBottom)
				{
					// Décrémenter le nombre de vies
					life--;
					ballAtBottom = true;
				}
				// Remettre la balle à sa position de départ
				ball.setPosition(startingBallPosition);
			}
			else
			{
				ballAtBottom = false;
			}
		}
		else {
			showEnd(window);
		}

		// Gestion des mouvements de la plateforme avec les touches du clavier
		float platformSpeed = 300.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			platform.move(-platformSpeed * elapsedTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			platform.move(platformSpeed * elapsedTime);
		}

		// Déplacement de la balle en fonction du temps et gestion des collisions avec les bords de la fenêtre et la plateforme
		ball.move(elapsedTime);
		ball.manageCollisionWithWindow(window);

		/*	// Vérification si la balle dépasse la position Y à ne pas dépasser par rapport à la ligne
			if (ball.getPosition().y > maxBallPosY)
			{
				// Si la balle dépasse la position Y à ne pas dépasser, le joueur a perdu et on ferme la fenêtre
				window.close();
			}*/

			// Effacement de la fenêtre avant le dessin
		window.clear();

		// Dessin du fond noir
		windowRect.setFillColor(sf::Color(0, 0, 0));
		windowRect.setPosition(0, 0);
		window.draw(windowRect);

		// Déplacement de la plateforme en fonction du temps
		platform.update(elapsedTime);
		window.draw(lifeText);
		// Dessin de la plateforme et de la balle
		platform.draw(window);
		ball.draw(window);
		for (int i = 0; i < bricks.size(); i++)
		{
			if (bricks[i]->isAlive())
			{
				bricks[i]->draw(window);
				ball.manageCollisionWithBrick(bricks[i]);
			}
			else
			{
				bricks[i]->destroyAndDelete(bricks);
			}
		}

		// Affichage des dessins dans la fenêtre
		window.display();

		// Gestion des collisions entre la balle et la plateforme


		ball.manageCollisionWithPlatform(platform);

	}

	return 0;
}