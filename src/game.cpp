
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
	currentLevel = 0;
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
	if (menu)
	{

	}
	else
	{
		player.update(dt);

		levels[currentLevel].update(dt);

		// collisionDetect();


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

		if (player.getPosition().y + player.getSize().y > 500.f)
		{
			player.collision(
				sf::Vector2f(player.getPosition().x, 500.f - player.getSize().y),
				sf::Vector2f(player.getVelocity().x, 0),
				true);
		}
	}

	frames++;
	if (frameCounter.getElapsedTime().asMilliseconds() > 1000)
	{
		frameCounter.restart();
		frameText.setString(std::to_string(frames));
		frames = 0;
	}
}

void Game::collisionDetect()
{
	std::vector<Room> rooms = levels[currentLevel].collisionDetect(player.getPosition(), player.getSize());

	for (Room room : rooms)
	{
		int startX = (int(player.getPosition().x) - int(room.getPosition().x)) / Room::TileSize;
		int startY = (int(player.getPosition().y) - int(room.getPosition().y)) / Room::TileSize;
		startX = startX > 0 ? startX : 0;
		startY = startY > 0 ? startY : 0;

		for (int i = startX; (i < startX + int(player.getSize().x / Room::TileSize)) && (i < Room::Size); i++)
		{
			for (int j = startY; (j < startY + int(player.getSize().y / Room::TileSize)) && (j < Room::Size); j++)
			{

				if (room.getTileArray()[i][j] != 0)
				{
					// NOTE: Many potential points of failure here
					sf::FloatRect tileCollider = sf::FloatRect(
						room.getPosition() + (sf::Vector2f(i, j) * float(Room::TileSize)),
						sf::Vector2f(Room::TileSize, Room::TileSize));

					collisionManagement(
						sf::FloatRect(player.getPosition(), player.getSize()),
						tileCollider);
					
					return;
				}
			}
		}
	}
}

void Game::collisionManagement(sf::FloatRect object1, sf::FloatRect object2)
{
	// TODO: Find direction vector from object1 to object2
	// TODO: Move object1 away from object2 (using previous direction vector) so that they are 'just touching'
	// TODO: Find which axis (x or y) both objects majority align with (which sides are touching)
	// TODO: Player position is pushed out of object2 using the axis found and the assosiated velocity axis is set to 0 (player is grounded if the touching side is the bottom one)
}

void Game::render()
{
	window.setView(currentView);

	player.render(window);

	levels[currentLevel].render(window);

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