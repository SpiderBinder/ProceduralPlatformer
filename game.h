#include <SFML/Graphics.hpp>
#include "player.h"

class Game
{
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
};