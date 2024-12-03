
#include "game.h"

Game::Game(sf::RenderWindow& game_window) 
	: window(game_window)
{
	// For input checking
	menu = false;
	// For physics calculation
	gravity = 5.f;
	floor = 500.f; // NOTE: Temporary for testing

	// Misc
	frames = 0;
}

Game::~Game()
{
	frameCounter.restart();
}

bool Game::init()
{
	bool success = true;

	if (!player.init())
		success = false;

	levels.push_back(Level("Content/Levels/TestLevel/"));
	for (Level& level : levels)
	{
		if (!level.init())
			success = false;
	}

	playerView = window.getDefaultView();
	debugView = window.getDefaultView();
	currentViewType = ViewType::PlayerView;

	// Text for displaying debug info
	if (!debugFont.loadFromFile("Content/Text/Fonts/Pixeled.ttf"))
	{
		std::cout << "Error - debugFont failed to load" << std::endl;
		success = false;
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

	return success;
}

void Game::update(float dt)
{
	player.update(dt);

	for (Level& level : levels)
	{
		level.update(dt);
	}

	playerView.setCenter((player.getPosition() + (player.getSize() / 2.f)));

	switch (currentViewType)
	{
	case ViewType::PlayerView:
		currentView = playerView;
		break;
	case ViewType::DebugView:
		currentView = debugView;
		break;
	default:
		currentView = window.getDefaultView();
	}

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
	// TODO: Replace with Level collision and return player position to previous one if returns true
	// Also clamp associated velocity for whatever direction they were going?
	// NOTE: This may not be a very good way of doing collision physics, research into better methods

	if (player.getPosition().y + player.getSize().y > floor)
	{
		sf::Vector2f newPosition(player.getPosition().x, floor - player.getSize().y);
		player.collision(newPosition, player.getVelocity(), true);
	}
}

void Game::render()
{
	window.setView(currentView);

	player.render(window);

	for (Level& level : levels)
	{
		level.render(window);
	}

	sf::Vector2f viewCorner = currentView.getCenter() - (currentView.getSize() / 2.f);

	// General debug info
	frameText.setPosition(viewCorner + sf::Vector2f(currentView.getSize().x - 40, 10));
	window.draw(frameText);

	// Player debug info
	std::string positionDebug = "Position: " +
		std::to_string(player.getPosition().x) + ' ' +
		std::to_string(player.getPosition().y);

	std::string velocityDebug = "Velocity: " + 
		std::to_string(player.getVelocity().x) + ' ' +
		std::to_string(player.getVelocity().y);

	std::string accelerationDebug = "Acceleration: " +
		std::to_string(player.getAcceleration().x) + ' ' +
		std::to_string(player.getAcceleration().y);

	debugText.setString(positionDebug);
	debugText.setPosition(viewCorner + sf::Vector2f(10, 10));
	window.draw(debugText);
	debugText.setString(velocityDebug);
	debugText.setPosition(viewCorner + sf::Vector2f(10, 25));
	window.draw(debugText);
	debugText.setString(accelerationDebug);
	debugText.setPosition(viewCorner + sf::Vector2f(10, 40));
	window.draw(debugText);
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