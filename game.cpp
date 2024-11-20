
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

bool Game::Init()
{
	if (!player.Init())
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

void Game::Update(float dt)
{
	player.Update(dt);
	frames++;
	if (frameCounter.getElapsedTime().asMilliseconds() > 1000)
	{
		frameCounter.restart();
		frameText.setString(std::to_string(frames));
		frames = 0;
	}

	CollisionDetect();
}

void Game::CollisionDetect()
{
	if (player.Position().y + player.Size().y > floor)
	{
		sf::Vector2f newPosition(player.Position().x, floor - player.Size().y);
		player.Collision(newPosition, true);
	}
}

void Game::Render()
{
	player.Render(window);


	// General debug info
	// NOTE: Add frame rate display?

	// Player debug info
	std::string position = "Position: " +
		std::to_string(player.Position().x) + ' ' +
		std::to_string(player.Position().y);

	std::string velocity = "Velocity: " + 
		std::to_string(player.Velocity().x) + ' ' +
		std::to_string(player.Velocity().y);

	std::string acceleration = "Acceleration: " +
		std::to_string(player.Acceleration().x) + ' ' +
		std::to_string(player.Acceleration().y);

	debugText.setString(position);
	debugText.setPosition(10, 10);
	window.draw(debugText);
	debugText.setString(velocity);
	debugText.setPosition(10, 25);
	window.draw(debugText);
	debugText.setString(acceleration);
	debugText.setPosition(10, 40);
	window.draw(debugText);

	debugText.setString(std::to_string(player.Sliding()));
	debugText.setPosition(10, 55);
	window.draw(debugText);

	window.draw(frameText);
}

void Game::KeyboardEvent(sf::Event event)
{
	// Check for window focus
	if (!window.hasFocus())
		return;

	if (!menu)
	{
		player.KeyboardInput(event);
	}
	else
	{

	}
}

void Game::MouseEvent(sf::Event event)
{
	// NOTE: Currently unused
}