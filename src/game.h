
#ifndef _PROCEDURALPLATFORMER_GAME_H_
#define _PROCEDURALPLATFORMER_GAME_H_

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
	bool init();
	void update(float dt);
	void render();
	// Input Management
	void keyboardEvent(sf::Event event);
	void mouseEvent(sf::Event event);
	// Physics
	void collisionDetect();

	// Public get-only varaibles
	int readFrames() { return frames; }
};

#endif // _PROCEDURALPLATFORMER_GAME_H_