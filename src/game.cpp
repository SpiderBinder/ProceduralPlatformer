
#include "game.h"

Game::Game(sf::RenderWindow& game_window) 
	: window(game_window)
{
	// For input checking
	menu = false;
	// For physics calculation
	gravity = 5.f;
	floor = 500.f; // NOTE: Temporary for testing
}

Game::~Game()
{
	frameCounter.restart();
}

bool Game::init()
{
	if (!player.init())
		return false;

	// Text for displaying debug info
	if (!debugFont.loadFromFile("Content/Text/Fonts/Pixeled.ttf"))
	{
		std::cout << "Error - debugFont failed to load" << std::endl;
		return false;
	}
	debugText.setFont(debugFont);
	debugText.setFillColor(sf::Color(10, 10, 10, 255));
	debugText.setCharacterSize(10);
	debugText.setPosition(10, 10);

	frameText.setFont(debugFont);
	frameText.setFillColor(sf::Color(50, 200, 50, 200));
	frameText.setCharacterSize(8);
	frameText.setPosition(window.getSize().x - 40, 10);
	frameText.setString("0");

	frames = 0;

	return true;
}

void Game::update(float dt)
{
	player.update(dt);
	frames++;
	if (frameCounter.getElapsedTime().asMilliseconds() > 1000)
	{
		frameCounter.restart();
		frameText.setString(std::to_string(frames));
		frames = 0;
	}

	collisionDetect();
}

void Game::collisionDetect()
{
	if (player.readPosition().y + player.readSize().y > floor)
	{
		sf::Vector2f newPosition(player.readPosition().x, floor - player.readSize().y);
		player.collision(newPosition, player.readVelocity(), true);
	}
}

void Game::render()
{
	player.render(window);


	// General debug info
	// NOTE: Add frame rate display?

	// Player debug info
	std::string position = "Position: " +
		std::to_string(player.readPosition().x) + ' ' +
		std::to_string(player.readPosition().y);

	std::string velocity = "Velocity: " + 
		std::to_string(player.readVelocity().x) + ' ' +
		std::to_string(player.readVelocity().y);

	std::string acceleration = "Acceleration: " +
		std::to_string(player.readAcceleration().x) + ' ' +
		std::to_string(player.readAcceleration().y);

	debugText.setString(position);
	debugText.setPosition(10, 10);
	window.draw(debugText);
	debugText.setString(velocity);
	debugText.setPosition(10, 25);
	window.draw(debugText);
	debugText.setString(acceleration);
	debugText.setPosition(10, 40);
	window.draw(debugText);

	window.draw(frameText);
}

void Game::keyboardEvent(sf::Event event)
{
	// Check for window focus
	if (!window.hasFocus())
		return;

	if (!menu)
	{
		player.keyboardInput(event);
	}
	else
	{

	}
}

void Game::mouseEvent(sf::Event event)
{
	// NOTE: Currently unused
}