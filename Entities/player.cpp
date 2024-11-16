
#include "player.h"

// Constructor
Player::Player()
{
	position = sf::Vector2f(100.f, 100.f);

	// Physics
	runAcceleration = 3000.f;
	runSpeed = 300.f;
	jumpSpeed = 200.f;
	gravity = 1500.f;
	friction = 0.2f; // NOTE: Temporary value until individual material friction is added
	grounded = false;

	// Input
	moveLeft = false;
	moveRight = false;
	moveDown = false;
	moveJump = false;
}

Player::~Player()
{

}

bool Player::Init()
{
	bool success = true;

	// Loading Player Textures
	if (!idleTexture.loadFromFile("Content/Sprites/Player/Idle.png")) {
		std::cout << "Error - Player Idle.png failed to load" << std::endl;
		success = false;
	}
	if (!runTexture.loadFromFile("Content/Sprites/Player/Run.png")) {
		std::cout << "Error - Player Run.png failed to load" << std::endl;
		success = false;
	}

	if (!jumpIdleTexture.loadFromFile("Content/Sprites/Player/JumpIdle.png")) {
		std::cout << "Error - Player JumpIdle.png failed to load" << std::endl;
		success = false;
	}
	if (!jumpRunTexture.loadFromFile("Content/Sprites/Player/JumpRun.png")) {
		std::cout << "Error - Player JumpRun.png failed to load" << std::endl;
		success = false;
	}

	sprite.setTexture(idleTexture);
	sprite.setPosition(100.f, 100.f);
	sprite.setScale(2.f, 2.f);

	size.x = sprite.getGlobalBounds().width;
	size.y = sprite.getGlobalBounds().height;

	return success;
}

void Player::Update(float dt)
{
	// NOTE: Having a seperate thing for acceleration may be stupid idk
	acceleration.x = 0;
	acceleration.y = 0;


	if (!grounded)
	{
		// Applying gravity when not grounded (may not be needed)
		acceleration.y += gravity;
	}

	// Movement physics
	if (grounded)
	{
		acceleration.x += moveRight ? runAcceleration : 0;
		acceleration.x += moveLeft ? -runAcceleration : 0;
	}


	// Calculating resistance
	velocity.x -= dt *
		(grounded ? 8 : 0.2) * 
		(velocity.x + (velocity.x >= 0 ? 30 : -30));

	// Updating position from velocity
	velocity += acceleration * dt;
	position += velocity * dt;
	sprite.setPosition(position);
}

void Player::Collision(sf::Vector2f newPosition, bool ground)
{
	grounded = ground;
	position = newPosition;
	sprite.setPosition(newPosition);
}

void Player::Render(sf::RenderWindow& window)
{
	// Basic animation
	if (moveLeft == moveRight)
		// Stationary Texture
		sprite.setTexture(grounded ? idleTexture : jumpIdleTexture);
	else if (moveLeft)
	{
		// Running/Jump Running texture
		sprite.setTexture(grounded ? runTexture : jumpRunTexture);
		// Flip sprite left
		sprite.setTextureRect(sf::IntRect(
			sprite.getLocalBounds().width,
			0,
			-sprite.getLocalBounds().width,
			sprite.getLocalBounds().height));
	}
	else if (moveRight)
	{
		// Running/Jump Running texture
		sprite.setTexture(grounded ? runTexture : jumpRunTexture);
		// Flip sprite right
		sprite.setTextureRect(sf::IntRect(
			0, 0, sprite.getLocalBounds().width,
			sprite.getLocalBounds().height));
	}

	window.draw(sprite);
}

void Player::KeyboardInput(sf::Event event)
{
	// Checking if event is 'KeyPressed' or 'KeyReleased'
	bool keyPressed = event.type == sf::Event::KeyPressed;

	// Input cases
	switch (event.key.scancode)
	{
		// Moving right
	case sf::Keyboard::Scancode::D:
		moveRight = keyPressed ? true : false;
		break;
		// Moving left
	case sf::Keyboard::Scancode::A:
		moveLeft = keyPressed ? true : false;
		break;

		// Jumping
	case sf::Keyboard::Scancode::Space:
		if (grounded && keyPressed)
		{
			velocity.y = -jumpSpeed*3;
			grounded = false;
		}
		break;
	}
}

void Player::MouseInput(sf::Event event)
{
	// NOTE: Currently unused
}