#include <SFML/Graphics.hpp>

class Player
{
public:
	// Constructor
	Player();
	~Player();
	// Initialisation + Update/Render
	bool Init();
	void Update(float dt);
	void Render(sf::RenderWindow& window);
	// Input Management
	void KeyboardInput(sf::Event event);
	void MouseInput(sf::Event event);

	void Collision(sf::Vector2f newPosition, bool ground);

	sf::Vector2f Position() { return position; }
	sf::Vector2f Velocity() { return velocity; }
	sf::Vector2f Size() { return size; }

private:
	// Physics
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f size;
	float speed;
	float jumpSpeed;
	float gravity;
	bool grounded;
	// Input
	bool moveRight;
	bool moveLeft;
	bool moveDown;
	bool moveJump;
	// Sprites and Textures
	sf::Sprite sprite;
	sf::Texture idleTexture;
	sf::Texture runRightTexture;
	sf::Texture runLeftTexture;
	sf::Texture jumpIdleTexture;
	sf::Texture jumpRightTexture;
	sf::Texture jumpLeftTexture;
};