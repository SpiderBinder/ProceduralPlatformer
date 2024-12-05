
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
		dt = dt > 0.1 ? 0.1 : dt;

		player.update(dt);

		levels[currentLevel].update(dt);

		collisionDetect();


		playerView.setCenter((player.getBasePosition() + (player.getBaseSize() / 2.f)));

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

		/*if (player.getPosition().y + player.getSize().y > 500.f)
		{
			player.collision(
				sf::Vector2f(player.getPosition().x, 500.f - player.getSize().y),
				sf::Vector2f(player.getVelocity().x, 0),
				true);
		}*/
	}

	frames++;
	if (frameCounter.getElapsedTime().asMilliseconds() > 1000)
	{
		frameCounter.restart();
		frameText.setString(std::to_string(frames));
		frames = 0;
	}
}

// TODO: Fix horizontal collision
// TODO: In the future, checking for travelling clean-through a collider would be nice
// TODO: Add check for attempting to uncrouch to see if it would cause a collision when wouldn't otherwise and lock uncrouching
// NOTE: For this (^) you could uncouple collisionManagement from collisionDetect and have collisionDetect return the tile's collider (default rect if no collision) instead?
void Game::collisionDetect()
{
	std::vector<Room> rooms = levels[currentLevel].collisionDetect(player.getPosition(), player.getSize());

	for (Room room : rooms)
	{
		int startX = (int(player.getPosition().x) - int(room.getPosition().x)) / Room::TileSize;
		int startY = (int(player.getPosition().y) - int(room.getPosition().y)) / Room::TileSize;
		startX = startX > 0 ? startX : 0;
		startY = startY > 0 ? startY : 0;

		for (int i = startX; (i < startX + int(player.getSize().x / Room::TileSize) + 1) && (i < Room::Size); i++)
		{
			for (int j = startY; (j < startY + int(player.getSize().y / Room::TileSize) + 1) && (j < Room::Size); j++)
			{

				if (room.getTileArray()[i][j] != 0)
				{
					sf::FloatRect tileCollider = sf::FloatRect(
						room.getPosition() + (sf::Vector2f(i, j) * float(Room::TileSize)),
						sf::Vector2f(Room::TileSize, Room::TileSize));

					if (sf::FloatRect(player.getPosition(), player.getSize()).intersects(tileCollider))
					{
						collisionManagement(
							sf::FloatRect(player.getPosition(), player.getSize()),
							tileCollider,
							player.getVelocity());

						return;
					}
				}
			}
		}
	}
}

// NOTE: object1 is currently specifically the player (change?)
// Manages collision between a moving entity (object1) and a static one (object2)
void Game::collisionManagement(sf::FloatRect object1, sf::FloatRect object2, sf::Vector2f direction)
{
	sf::Vector2f newPosition = object1.getPosition();
	sf::Vector2f newVelocity = direction;
	int side;

	if (direction.y == 0 || direction.x == 0)
	{
		if (direction.y == 0)
			side = direction.x > 0 ? 3 : 1;
		else if (direction.x == 0)
			side = direction.y > 0 ? 0 : 2;
		else
			side = 0;
	}
	else
	{
		sf::Vector2f corner1 = object1.getPosition();
		sf::Vector2f corner2 = object2.getPosition();
		sf::Vector2i cornerDirection;

		// Finds if corner1 should be of the right two or left two (opposite for corner2)
		if (direction.x > 0)
		{
			corner1.x += object1.getSize().x;
			cornerDirection.x = -1;
		}
		else
		{
			corner2.x += object2.getSize().x;
			cornerDirection.x = 1;
		}
		// Finds if corner1 should be of the bottom two or top two (opposite for corner2)
		if (direction.y > 0)
		{
			corner1.y += object1.getSize().y;
			cornerDirection.y = -1;
		}
		else
		{
			corner2.y += object2.getSize().y;
			cornerDirection.y = 1;
		}

		// NOTE: BIG point of potential failure here
		// Checks which side of corner2 the direction 'passes through'
		float differenceX = (direction.x / direction.y) * (corner2.y + direction.y - corner1.y);
		bool right = corner1.x + differenceX > corner2.x;
		
		if (cornerDirection.x > 0)
			side = right ? 1 : (cornerDirection.y > 0 ? 2 : 0);
		else
			side = right ? (cornerDirection.y > 0 ? 2 : 0) : 3;
	}

	switch (side)
	{
	default:
	case 0:
		newPosition.y = object2.getPosition().y - object1.getSize().y;
		newVelocity.y = 0;
		break;
	case 1:
		newPosition.x = object2.getPosition().x + object2.getSize().x;
		newVelocity.x = 0;
		break;
	case 2:
		newPosition.y = object2.getPosition().y + object2.getSize().y;
		newVelocity.y = 0;
		break;
	case 3:
		newPosition.x = object2.getPosition().x - object1.getSize().x;
		newVelocity.x = 0;
		break;
	}

	player.collision(newPosition, newVelocity, side == 0);

	return;
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