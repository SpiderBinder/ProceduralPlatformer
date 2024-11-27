
#include "level.h"


Level::Level(std::string roomDirectory, std::string textureDirectory)
	: roomDirectory(roomDirectory), textureDirectory(textureDirectory)
{

}

bool Level::init()
{
	bool success = true;

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

	return success;
}

void Level::loadRooms()
{

}

void Level::generate()
{

}

void Level::update(float dt)
{
	// NOTE: Update 'loadedRooms' with rooms directly surrounding/containing player here

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

sf::Vector2f Level::collisionDetect(sf::FloatRect playerCollider)
{
	sf::Vector2f positionUpdate;



	return positionUpdate;
}