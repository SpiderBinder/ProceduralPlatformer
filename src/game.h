
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
	bool menu; // Gamestate boolean
	int frames; // Elapsed frames since the last second
	sf::Clock frameCounter; // Timer that resets every second to count frames

	// Player character (singular instance of the 'Player' class)
	Player player;

	// Environment
	float gravity; // Global gravity value
	float floor; // NOTE: Temp for testing; Remove after implemented level and collision

	// Fonts and Texts
	sf::Font debugFont; // Default font
	sf::Text debugText; // Text used for debug info
	sf::Text frameText; // Text used for frame rate display

public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	// Input Management
	void keyboardEvent(sf::Event event);
	void mouseEvent(sf::Event event);
	// Physics Engine
	void collisionDetect();

	// Public get-only varaibles
	int getFrames() { return frames; }
};

#endif // _PROCEDURALPLATFORMER_GAME_H_