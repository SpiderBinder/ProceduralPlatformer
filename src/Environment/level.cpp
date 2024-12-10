
#include "level.h"


Level::Level(std::string directory)
{
	roomDirectory = (directory + "RoomTypes/");
	textureDirectory = (directory + "Textures/");
}

bool Level::init()
{
	bool success = true;

	// NOTE: Temporary for testing, will be replaced with reading all textures from files
	textureNames.push_back("defTile.png");
	textureNames.push_back("defTile.png");

	for (int i = 0; i < textureNames.size(); i++)
	{
		textures.push_back(sf::Texture());
		if (!textures[i].loadFromFile(textureDirectory + textureNames[i]))
		{
			std::cout << textureNames[i] << " failed to load" << std::endl;
			success = false;
		}
	}

	// NOTE: Temporarily unused as file reading and generation not implemented
	loadRooms();
	// generate(int seed);

	// NOTE: tempArray and the manual addition of a room is temporary for testing

	rooms.push_back(Room(roomPresets.at(0), sf::Vector2f(0, 0)));

	return success;
}

void Level::loadRooms()
{
	for (auto const& entry : std::filesystem::directory_iterator(roomDirectory))
	{
		// Reading contents of file
		std::vector<std::string> contents;
		std::string tempString;
		std::ifstream readFile(entry.path());

		while (std::getline(readFile, tempString, ';'))
		{
			contents.push_back(tempString);
		}

		// Assigning contents of file to a room object
		std::string name;
		std::array<std::array<int, Room::Size>, Room::Size> body;
		std::array<int, Room::Size> tempArray;
		tempArray.fill(0);
		body.fill(tempArray);

		for (std::string variable : contents)
		{
			std::string code = variable.substr(0, variable.find('='));
			std::string value = variable.substr(variable.find('=') + 1);

			code.erase(std::remove(code.begin(), code.end(), '\n'), code.end());

			if (code == "name")
			{
				name = value;
			}
			if (code == "body")
			{
				value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
				int counter = 0;
				for (int i = 0; i < Room::Size; i++)
				{
					for (int j = 0; j < Room::Size; j++)
					{
						int cutPosition = value.find(',');
						body[i][j] = stoi(value.substr(counter, cutPosition));
						counter += cutPosition + 1;
					}
				}
			}
		}

		roomPresets.push_back(Room(body, name));

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


// Returns the collider rectangle of the requested tile type
sf::FloatRect Level::getTileCollider(int tileType)
{
	if (tileType <= 0 || tileType > textures.size())
	{
		return sf::FloatRect();
	}
	// TODO: Make this change based on tile type (Level object will contain list of rects)
	return sf::FloatRect(0, 0, Room::TileSize, Room::TileSize);
}

// Returns vector of rooms the collider is contained within
std::vector<Room> Level::collisionDetect(sf::Vector2f position, sf::Vector2f size)
{
	std::vector<Room> withinRooms;

	for (Room room : loadedRooms)
	{
		if (position.x < room.getPosition().x + (Room::Size * Room::TileSize) &&
			position.x + size.x > room.getPosition().x &&
			position.y < room.getPosition().y + (Room::Size * Room::TileSize) &&
			position.y + size.y > room.getPosition().y)
		{
			withinRooms.push_back(room);
		}
	}

	// NOTE: Temporary for testing
	return loadedRooms;

	return withinRooms;
}