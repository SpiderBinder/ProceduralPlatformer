
#include "room.h"

Room::Room()
{
	std::array<int, Size> tempArray;
	tempArray.fill(0);
	tileArray.fill(tempArray);

	position = sf::Vector2f(0, 0);
	id = 0;
}

Room::Room(std::array<std::array<int, Size>, Size> tileArray, std::string roomType)
	: tileArray(tileArray), roomType(roomType)
{
	position = sf::Vector2f(0, 0);
	id = 0;
}

Room::Room(std::array<std::array<int, Size>, Size> tileArray, std::string roomType, sf::Vector2f position)
	: tileArray(tileArray), roomType(roomType), position(position)
{
	// TODO: Make system for creating unique id from float position of room
}

void Room::update(float dt)
{

}

void Room::render(sf::RenderWindow& window, std::vector<sf::Texture> textures)
{
	sf::Vector2f tempVector = position;

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			// Checks if there is a texture provided for the tileType of the currently drawn tile
			if (tileArray[i][j] < textures.size())
			{
				// Checks if the tileType is 'Empty'/default (0)
				if (tileArray[i][j] != 0)
				{
					sprite.setPosition(tempVector);
					sprite.setTexture(textures[tileArray[i][j]]);
					window.draw(sprite);
				}
			}
			else
			{
				std::cout << "Error - No texture found for tileType" << std::endl;
				continue;
			}

			tempVector.y += sprite.getGlobalBounds().height;
		}
		tempVector.x += sprite.getGlobalBounds().width;
		tempVector.y = position.y;
	}
}

// Checks if a point is within a solid tile in the room
// NOTE: May be currently useless
bool Room::withinTile(sf::Vector2f point)
{
	point -= position;
	point = sf::Vector2f(int(point.x) / int(TileSize), int(point.y) / int(TileSize));
	
	if (tileArray[point.x][point.y] > 0)
		return true;

	return false;
}