
#include "room.h"

Room::Room()
{
	std::array<int, size> tempArray;
	tempArray.fill(0);
	tileArray.fill(tempArray);

	position = sf::Vector2i(0, 0);
	id = 0;
}

Room::Room(std::array<std::array<int, size>, size> tileArray, std::string roomType)
	: tileArray(tileArray), roomType(roomType)
{
	position = sf::Vector2i(0, 0);
	id = 0;
}

Room::Room(std::array<std::array<int, size>, size> tileArray, std::string roomType, sf::Vector2i position)
	: tileArray(tileArray), roomType(roomType), position(position)
{
	id = position.x * 10000 + position.y;
}

void Room::update(float dt)
{

}

void Room::render(sf::RenderWindow& window, sf::Texture textures[15])
{
	sf::Vector2f tempVector = sf::Vector2f(position);
	tempVector *= float(size);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sprite.setPosition(tempVector);
			sprite.setTexture(textures[tileArray[i][j]]);
			window.draw(sprite);

			tempVector.y++;
		}
		tempVector.x++;
	}
}