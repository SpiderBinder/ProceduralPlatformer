
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
	std::array<std::array<int, Room::Size>, Room::Size> tempArray;
	tempArray[0].fill(1);
	tempArray[Room::Size - 1].fill(1);
	for (int i = 1; i < Room::Size - 1; i++)
	{
		tempArray[i].fill(0);
		tempArray[i][0] = 1;
		tempArray[i][Room::Size - 1] = 1;
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

// Returns vector of rooms the collider is contained within
std::vector<Room> Level::collisionDetect(sf::Vector2f position, sf::Vector2f size)
{
	std::vector<Room> withinRooms;

	for (Room room : loadedRooms)
	{
		if (position.x < room.getPosition().x + Room::Size &&
			position.x + size.x > room.getPosition().x &&
			position.y < room.getPosition().y + Room::Size &&
			position.y + size.y > room.getPosition().y)
		{
			withinRooms.push_back(room);
		}
	}

	return withinRooms;
}