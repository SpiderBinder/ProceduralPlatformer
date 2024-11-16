
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>


#include "Entities/player.h"
#include "Environment/level.h"

class Game
{
private:
	// Misc
	sf::RenderWindow& window;
	bool menu;

	// Player
	Player player;

	// Environment
	float gravity;
	float floor; // Temp for testing; Remove after implemented level and collision

	// Fonts and Texts
	sf::Font debugFont;
	sf::Text debugText;

public:
	// Constructor and basic game loop
	Game(sf::RenderWindow& window);
	~Game();
	bool Init();
	void Update(float dt);
	void Render();
	// Input Management
	void KeyboardEvent(sf::Event event);
	void MouseEvent(sf::Event event);

	void CollisionDetect();

};