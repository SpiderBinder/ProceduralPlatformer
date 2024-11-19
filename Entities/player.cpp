
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
	friction = 1.f; // NOTE: Temporary value until individual material friction is added
	grounded = false;

	// Input
	moveLeft = false;
	moveRight = false;
	crouch = false;
	jump = false;
	slide = false;
}

Player::~Player()
{

}

bool Player::Init()
{
	bool success = true;

	// Loading Player Textures
	if (!idleTexture.loadFromFile("Content/Sprites/Player/Idle.png")) {
		std::cout << "Error - Player \'Idle.png\' failed to load" << std::endl;
		success = false;
	}
	if (!runTexture.loadFromFile("Content/Sprites/Player/Run.png")) {
		std::cout << "Error - Player \'Run.png\' failed to load" << std::endl;
		success = false;
	}

	if (!jumpIdleTexture.loadFromFile("Content/Sprites/Player/JumpIdle.png")) {
		std::cout << "Error - Player \'JumpIdle.png\' failed to load" << std::endl;
		success = false;
	}
	if (!jumpRunTexture.loadFromFile("Content/Sprites/Player/JumpRun.png")) {
		std::cout << "Error - Player \'JumpRun.png\' failed to load" << std::endl;
		success = false;
	}

	if (!crouchTexture.loadFromFile("Content/Sprites/Player/Crouch.png")) {
		std::cout << "Error - Player \'Crouch.png\' failed to load" << std::endl;
		success = false;
	}
	if (!slideTexture.loadFromFile("Content/Sprites/Player/Slide.png")) {
		std::cout << "Error - Player \'Slide.png\' failed to load" << std::endl;
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
	animation = Idle;

	// Updating collision box
	size.y = crouch ? 96.f : 128.f;

	// NOTE: Having a seperate thing for acceleration may be stupid idk
	acceleration.x = 0;
	acceleration.y = 0;

	// Applying gravity
	acceleration.y += crouch ? gravity * 2 : gravity;

	// Movement physics
	if (moveRight && !slide)
	{
		acceleration.x += runAcceleration *
			(!crouch ? 1 : 0.4) *
			(grounded ? 1 : 0.3);
		animation = grounded ? Run : JumpRun;
	}
	if (moveLeft && !slide)
	{
		acceleration.x += -runAcceleration *
			(!crouch ? 1 : 0.4) *
			(grounded ? 1 : 0.3);
		animation = grounded ? Run : JumpRun;
	}
	if (slide)
	{
		// NOTE: Put stuff here plz thx
	}
	if (moveLeft == moveRight)
		animation = grounded ? Idle : JumpIdle;
	if (crouch)
		animation = Crouch;


	// Calculating resistance
	float totalFriction = friction * (grounded ? (slide ? 2 : 8) : 1);
	float airResistance = velocity.x + (velocity.x >= 0 ? 30 : -30);
	velocity.x -= dt * totalFriction * airResistance;

	// Updating position from velocity
	velocity += acceleration * dt;
	position += velocity * dt;
	sprite.setPosition(position);
}

void Player::Collision(sf::Vector2f newPosition, bool ground)
{
	grounded = ground;
	if (grounded)
		velocity.y = 0;
	position = newPosition;
	sprite.setPosition(newPosition);
}

void Player::Render(sf::RenderWindow& window)
{
	// Basic 'animation'
	switch (animation)
	{
	case Idle:
		sprite.setTexture(idleTexture, true);
		break;
	case Run:
		sprite.setTexture(runTexture, true);
		break;
	case JumpIdle:
		sprite.setTexture(jumpIdleTexture, true);
		break;
	case JumpRun:
		sprite.setTexture(jumpRunTexture, true);
		break;
	case Crouch:
		sprite.setTexture(crouchTexture, true);
		break;
	case Slide:
		sprite.setTexture(slideTexture, true);
		break;

	default:
		sprite.setTexture(idleTexture, true);
		break;
	}

	if (moveLeft)
	{
		// Flip sprite left
		sprite.setTextureRect(sf::IntRect(
			sprite.getLocalBounds().width,
			0,
			-sprite.getLocalBounds().width,
			sprite.getLocalBounds().height));
	}
	else if (moveRight)
	{
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
		jump = keyPressed ? true : false;
		if (grounded && jump)
		{
			velocity.y = -jumpSpeed * 3;
			grounded = false;
		}
		break;
	// Crouching
	case sf::Keyboard::Scancode::LControl:
	case sf::Keyboard::Scancode::S:
		crouch = keyPressed ? true : false;
		break;
	// Sliding
	case sf::Keyboard::Scancode::LShift:
		slide = keyPressed ? true : false;
		break;
	}
}

void Player::MouseInput(sf::Event event)
{
	// NOTE: Currently unused
}