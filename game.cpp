
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

	return true;
}

void Game::Update(float dt)
{
	player.Update(dt);

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