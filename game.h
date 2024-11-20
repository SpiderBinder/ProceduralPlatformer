
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
	int frames;
	sf::Clock frameCounter;

	// Player
	Player player;

	// Environment
	float gravity;
	float floor; // Temp for testing; Remove after implemented level and collision

	// Fonts and Texts
	sf::Font debugFont;
	sf::Text debugText;
	sf::Text frameText;

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
	// Physics
	void CollisionDetect();

	// Public get-only varaibles
	int Frames() { return frames; }
};