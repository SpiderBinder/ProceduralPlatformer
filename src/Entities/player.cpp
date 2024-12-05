
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

	inputQueued = false;

	animation = Idle;
}

Player::~Player()
{

}


bool Player::init()
{
	bool success = true;

	// Loading Player Textures
	if (!idleTexture.loadFromFile("Content/Player/Textures/Idle.png")) {
		std::cout << "Error - Player \'Idle.png\' failed to load" << std::endl;
		success = false;
	}

	if (!runTexture.loadFromFile("Content/Player/Textures/Run.png")) {
		std::cout << "Error - Player \'Run.png\' failed to load" << std::endl;
		success = false;
	}
	if (!skidTexture.loadFromFile("Content/Player/Textures/Skid.png")) {
		std::cout << "Error - Player \'Skid.png\' failed to load" << std::endl;
		success = false;
	}

	if (!jumpIdleTexture.loadFromFile("Content/Player/Textures/JumpIdle.png")) {
		std::cout << "Error - Player \'JumpIdle.png\' failed to load" << std::endl;
		success = false;
	}
	if (!jumpRunTexture.loadFromFile("Content/Player/Textures/JumpRun.png")) {
		std::cout << "Error - Player \'JumpRun.png\' failed to load" << std::endl;
		success = false;
	}

	if (!crouchTexture.loadFromFile("Content/Player/Textures/Crouch.png")) {
		std::cout << "Error - Player \'Crouch.png\' failed to load" << std::endl;
		success = false;
	}
	if (!slideTexture.loadFromFile("Content/Player/Textures/Slide.png")) {
		std::cout << "Error - Player \'Slide.png\' failed to load" << std::endl;
		success = false;
	}

	sprite.setTexture(idleTexture);
	sprite.setPosition(100.f, 100.f);
	sprite.setScale(2.f, 2.f);

	size.x = sprite.getGlobalBounds().width;
	size.y = sprite.getGlobalBounds().height;
	baseSize = size;

	return success;
}


void Player::update(float dt)
{
	// Ungrounded input handling
	if (inputClock.getElapsedTime().asMilliseconds() > 150)
		inputQueued = false;
	if (grounded && inputQueued)
	{
		keyboardInput(inputQueue);

		inputQueued = false;
	}

	// Superjump logic
	if (crouch)
	{
		superjumpClock.restart();
	}

	animation = Idle;

	// Updating collision box
	if (crouch)
		size.y = baseSize.y * 0.75;
	else if (slide)
		size.y = baseSize.y * 0.5;
	else
		size.y = baseSize.y;

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
			(grounded ? 1 : 0.2);
		animation = grounded ? Run : JumpRun;
	}
	if (moveLeft && !slide)
	{
		acceleration.x += -runAcceleration *
			(!crouch ? 1 : 0.4) *
			(grounded ? 1 : 0.2);
		animation = grounded ? Run : JumpRun;
	}

	if (moveLeft == moveRight)
	{
		animation = grounded ? Idle : JumpIdle;
		if (abs(velocity.x) > 10 && grounded)
		{
			animation = Skid;
		}
		slide = false;
	}
	else if (slide)
	{
		animation = Slide;
		slide = grounded && (abs(velocity.x) > 100 && grounded);
		position.y -= !slide * baseSize.y * 0.5;
	}
	if (crouch)
	{
		animation = Crouch;
		slide = false;
	}

	// Calculating resistance
	// TODO: Prevent this from applying (and set velocity to 0 instead) when velocity is <1
	float totalFriction = friction * (grounded ? (slide ? 0.5 : 8) : 1);
	float airResistance = velocity.x + (velocity.x >= 0 ? 30 : -30);
	velocity.x -= dt * totalFriction * airResistance;

	// Updating position from velocity
	velocity += acceleration * dt;
	position += velocity * dt;

	basePosition = sf::Vector2f(position.x, (position.y + size.y) - baseSize.y);

	grounded = false;
}


void Player::render(sf::RenderWindow& window)
{
	sprite.setPosition(position);

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
	case Skid:
		sprite.setTexture(skidTexture, true);
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


void Player::collision(sf::Vector2f newPosition, sf::Vector2f newVelocity, bool ground)
{
	grounded = ground;
	position = newPosition;
	velocity = newVelocity;

	if (grounded)
		velocity.y = 0;
	sprite.setPosition(newPosition);
}


void Player::keyboardInput(sf::Event event)
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
		if (!grounded)
		{
			inputQueue = event;
			inputQueued = true;
			inputClock.restart();
			break;
		}

		jump = keyPressed ? true : false;
		if (jump)
		{
			if (superjumpClock.getElapsedTime().asMilliseconds() < 100 && !crouch)
				velocity.y = -jumpSpeed * 4;
			else
				velocity.y = -jumpSpeed * 3;

			if (slide)
				velocity.x += velocity.x > 0 ? 100 : -100;
		}
		break;
	// Crouching
	case sf::Keyboard::Scancode::LControl:
	case sf::Keyboard::Scancode::S:
		if (!crouch && keyPressed)
			position.y += baseSize.y * 0.25;
		else if (crouch && !keyPressed)
			position.y -= baseSize.y * 0.25;

		crouch = keyPressed ? true : false;
		break;
		
	// Sliding
	case sf::Keyboard::Scancode::LShift:
		if (!grounded)
		{
			inputQueue = event;
			inputQueued = true;
			inputClock.restart();
			break;
		}
		
		if (keyPressed)
		{
			// NOTE: Make sure (at some point) sliding cannot be initiated when it would cause clipping
			if ((moveLeft && velocity.x < -250) ||
				(moveRight && velocity.x > 250))
			{
				position.y += !slide * baseSize.y * 0.5;
				slide = true;
			}
		}
		else
		{
			position.y -= slide * baseSize.y * 0.5;
			slide = false;
		}

		break;
	}
}

void Player::mouseInput(sf::Event event)
{
	// NOTE: Currently unused
}

