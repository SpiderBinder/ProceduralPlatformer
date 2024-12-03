
#include "level.h"


Level::Level(std::string directory)
{
	roomDirectory = (directory + "RoomTypes/");
	textureDirectory = (directory + "Textures/");
}

bool Level::init()
{
	bool success = true;

	// NOTE: Temporary for testing? (only the second one)
	textureNames[0] = "defTile.png";
	textureNames[1] = "defTile.png";

	int i = 0;
	for (sf::Texture &texture : textures)
	{
		if (textureNames[i] == "") { break; }
		if (!texture.loadFromFile(textureDirectory + textureNames[i]))
		{
			std::cout << textureNames[i] << " failed to load" << std::endl;
			success = false;
		}
		i++;
	}

	// NOTE: Temporarily unused as file reading and generation not implemented
	// loadRooms();
	// generate(int seed);

	// NOTE: tempArray and the manual addition of a room is temporary for testing
	std::array<std::array<int, Room::getSize>, Room::getSize> tempArray;
	tempArray[0].fill(1);
	tempArray[Room::getSize - 1].fill(1);
	for (int i = 1; i < Room::getSize - 1; i++)
	{
		tempArray[i].fill(0);
		tempArray[i][0] = 1;
		tempArray[i][Room::getSize - 1] = 1;
	}

	rooms.push_back(Room(tempArray, "tempType", sf::Vector2f(0.f, 0.f)));

	return success;
}

void Level::loadRooms()
{
	// NOTE: Code to test functionality of std::filesystem
	for (auto const& entry : std::filesystem::directory_iterator(roomDirectory))
	{
		std::cout << entry.path() << std::endl;
	}
}

void Level::generate()
{

}

void Level::update(float dt)
{
	// TODO: Update 'loadedRooms' with rooms directly surrounding/containing player here

	// NOTE: Temporary for testing purposes
	loadedRooms = rooms;

	for (Room room : loadedRooms)
	{
		room.update(dt);
	}
}

void Level::render(sf::RenderWindow& window)
{
	for (Room room : loadedRooms)
	{
		room.render(window, textures);
	}
}

bool Level::collisionDetect(sf::FloatRect collider)
{
	//bool collision = false;

	// Cycles through all loaded rooms
	for (Room room : loadedRooms)
	{
		// Creats a temporary rect to check if the collider is within the room
		sf::FloatRect roomRect = sf::FloatRect(
			room.getPosition(),
			sf::Vector2f(room.getSize, room.getSize) * room.getTileSize().x);

		if (!roomRect.intersects(collider))
			continue;

		// Gets the tile array position of the top left collider corner
		int startX = int(collider.getPosition().x - room.getPosition().x) / int(room.getTileSize().x);
		int startY = int(collider.getPosition().y - room.getPosition().y) / int(room.getTileSize().y);
		startX = startX < 0 ? 0 : startX;
		startY = startY < 0 ? 0 : startY;
		// Gets the tile array position of the bottom right collider corner
		int endX = int(collider.getSize().x) / int(room.getTileSize().x) + startX;
		int endY = int(collider.getSize().y) / int(room.getTileSize().y) + startY;
		endX = endX > room.getSize ? room.getSize : endX;
		endY = endY > room.getSize ? room.getSize : endY;

		// Loops through all tiles intersecting the collider
		for (int i = startX; i < endX; i++)
		{
			for (int j = startY; j < endY; j++)
			{
				if (room.getTileArray()[i][j] != 0)
				{
					return true;
				}
			}
		}
	}

	return false;
}