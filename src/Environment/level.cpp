
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

sf::Vector2f Level::collisionDetect(sf::FloatRect collider, sf::FloatRect pastCollider)
{
	sf::Vector2f positionUpdate;
	sf::Vector2i direction;

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
				if (room.getTileArray()[i][j] == 0)
					continue;

				direction.x += i == startX ? -1 : (i == endX ? 1 : 0);
				direction.y += j == startY ? -1 : (j == endY ? 1 : 0);
			}
		}
	}



	return positionUpdate;
}