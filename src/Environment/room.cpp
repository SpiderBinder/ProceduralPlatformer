
#include "room.h"

Room::Room(std::array<std::array<int, size>, size> tileArray)
	:tileArray(tileArray)
{

}

void Room::update(float dt)
{

}

void Room::render(sf::RenderWindow& window, sf::Texture textures[15])
{

}

bool Room::collisionDetect(sf::IntRect playerRect)
{


	return false;
}