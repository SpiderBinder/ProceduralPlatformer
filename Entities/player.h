
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

class Player
{
private:
	// Physics
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f size;
	sf::Vector2f baseSize;

	float runAcceleration;
	float runSpeed;
	float jumpSpeed;
	float gravity;
	float friction;
	float airResistance;

	bool grounded;

	// Handling 'early' inputs
	// Grounded inputs done right before becoming grounded
	sf::Clock inputClock;
	sf::Event inputQueue; // NOTE: Potentially temporary name
	bool inputQueued;

	// Recording time between releasing a crouch and jumping
	sf::Clock superjumpClock;

	// Input
	bool moveRight;
	bool moveLeft;
	bool crouch;
	bool jump;
	bool slide;
	// Sprites and Textures
	sf::Sprite sprite;
	sf::Texture idleTexture;

	sf::Texture runTexture;
	sf::Texture skidTexture;
	sf::Texture jumpIdleTexture;
	sf::Texture jumpRunTexture;

	sf::Texture crouchTexture;
	sf::Texture slideTexture;

	enum State
	{
		Idle,
		Run,
		Skid,
		JumpIdle,
		JumpRun,
		Crouch,
		Slide
	};
	State animation; // NOTE: Should rename probably

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
	sf::Vector2f Acceleration() { return acceleration; }
	sf::Vector2f Size() { return size; }
};