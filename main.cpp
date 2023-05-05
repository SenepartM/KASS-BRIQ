#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>
// Fonction pour mapper une valeur d'une plage � une autre
double mapValue(double value, double min, double max, double nMin, double nMax)
{
	double newVal = (((value - min) / (max - min)) * (nMax - nMin)) + nMin;
	return newVal;
}

// Fonction pour afficher le menu et attendre que l'utilisateur appuie sur Espace pour lancer la partie
void showEnd(sf::RenderWindow& window) {
	// Chargement de la police de caract�res par d�faut
	sf::Font font;
	if (!font.loadFromFile("Fonts/bradybun.ttf"))
	{
		std::cout << "Erreur lors du chargement de la police" << std::endl;
		return;
	}

	// D�finition du texte � afficher dans le menu
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

	// Boucle pour afficher le menu tant que l'utilisateur n'appuie pas sur Espace ou Entr�e
	bool menuActive = true;
	while (menuActive)
	{
		// Gestion des �v�nements de la fen�tre
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

		// Effacement de la fen�tre avant le dessin
		window.clear();

		// Dessin du titre et du texte pour lancer la partie
		window.draw(title);
		window.draw(lose);
		window.draw(startText);

		// Affichage des dessins dans la fen�tre
		window.display();
	}
}


void showMenu(sf::RenderWindow& window)
{
	// Chargement de la police de caract�res par d�faut
	sf::Font font;
	if (!font.loadFromFile("Fonts/bradybun.ttf"))
	{
		std::cout << "Erreur lors du chargement de la police" << std::endl;
		return;
	}



	// D�finition du texte � afficher dans le menu
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
		// Gestion des �v�nements de la fen�tre
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

		// Effacement de la fen�tre avant le dessin
		window.clear();

		// Dessin du titre et du texte pour lancer la partie
		window.draw(title);
		window.draw(startText);

		// Affichage des dessins dans la fen�tre
		window.display();
	}
}


int main()
{

	// Cr�ation de la plateforme, de la balle, des bricks et de la fen�tre
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
	for (int i = 0; i < 4; i++) { // Boucle pour cr�er 4 lignes de bricks
		for (int j = 0; j < numBricksPerLine; j++) { // Boucle pour cr�er le nombre de briques sp�cifi� par ligne
			int x = horizontalSpacing + j * (brickWidth + horizontalSpacing); // Position x de la brick en fonction de j
			int y = verticalSpacing + i * (brickHeight + verticalSpacing); // Position y de la brick en fonction de i
			bricks.push_back(new Brick(x, y, brickWidth, brickHeight, 3)); // Cr�ation d'une nouvelle brick et ajout dans la deque
		}
	}




	// D�finition du rectangle qui sera utilis� pour dessiner la fen�tre
	sf::RectangleShape windowRect;
	windowRect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	// Variables pour le temps, la position de la souris, le temps �coul� et la position Y � ne pas d�passer par la balle par rapport � la plateforme
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
	// Boucle principale pour maintenir la fen�tre ouverte
	while (window.isOpen())
	{
		lifeText.setString("Vie : " + std::to_string(life)); // o� 'life' est la variable contenant la valeur de la vie
		lifeText.setPosition(10, 5); // ajustez la position du texte � votre guise
		window.draw(lifeText);
		// Calcul du temps �coul� depuis la derni�re it�ration de la boucle
		elapsedTime = clock.restart().asSeconds();

		// Gestion des �v�nements de la fen�tre
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Fermeture de la fen�tre si l'utilisateur le demande
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// V�rifiez si la balle a atteint le bas de l'�cran
	 // V�rifier si la balle a touch� le bas de l'�cran
		bool ballAtBottom = false;
		// D�finir la ligne de d�part pour la balle
		float ballStartLine = 250.f;

		// G�n�rer une position al�atoire horizontale pour la balle
		float ballStartX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (600 - 10);

		// D�finir la position de d�part de la balle
		sf::Vector2f startingBallPosition(ballStartX, ballStartLine);



		if (life > 0) {
			if (ball.getPosition().y > maxBallPosY)
			{
				if (!ballAtBottom)
				{
					// D�cr�menter le nombre de vies
					life--;
					ballAtBottom = true;
				}
				// Remettre la balle � sa position de d�part
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

		// D�placement de la balle en fonction du temps et gestion des collisions avec les bords de la fen�tre et la plateforme
		ball.move(elapsedTime);
		ball.manageCollisionWithWindow(window);

		/*	// V�rification si la balle d�passe la position Y � ne pas d�passer par rapport � la ligne
			if (ball.getPosition().y > maxBallPosY)
			{
				// Si la balle d�passe la position Y � ne pas d�passer, le joueur a perdu et on ferme la fen�tre
				window.close();
			}*/

			// Effacement de la fen�tre avant le dessin
		window.clear();

		// Dessin du fond noir
		windowRect.setFillColor(sf::Color(0, 0, 0));
		windowRect.setPosition(0, 0);
		window.draw(windowRect);

		// D�placement de la plateforme en fonction du temps
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

		// Affichage des dessins dans la fen�tre
		window.display();

		// Gestion des collisions entre la balle et la plateforme


		ball.manageCollisionWithPlatform(platform);

	}

	return 0;
}