
#include <SFML/Graphics.hpp>

#ifndef _PROCEDURALPLATFORMER_ENTITIES_PLAYER_H_
#define _PROCEDURALPLATFORMER_ENTITIES_PLAYER_H_

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
	bool init();
	void update(float dt);
	void render(sf::RenderWindow& window);
	// Input Management
	void keyboardInput(sf::Event event);
	void mouseInput(sf::Event event);

	void collision(sf::Vector2f newPosition, sf::Vector2f newVelocity, bool ground = false);

	sf::Vector2f readPosition() { return position; }
	sf::Vector2f readVelocity() { return velocity; }
	sf::Vector2f readAcceleration() { return acceleration; }
	sf::Vector2f readSize() { return size; }
};

#endif // _PROCEDURALPLATFORMER_ENTITIES_PLAYER_H_