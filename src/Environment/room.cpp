
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

void Room::render(sf::RenderWindow& window, std::array<sf::Texture, 15> textures)
{
	sf::Vector2f tempVector = position;

	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			sprite.setPosition(tempVector);
			sprite.setTexture(textures[tileArray[i][j]]);
			if (tileArray[i][j] != 0 )
				window.draw(sprite);

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