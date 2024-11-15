
#include "level.h"


// Start of 'Room' class members
Room::Room(std::array<std::array<int, size>, size> tileArray)
	:tileArray(tileArray)
{
	
}

void Room::Update(float dt)
{

}

void Room::Render(sf::RenderWindow& window, sf::Texture textures[15])
{
	
}

bool Room::CollisionDetect(sf::IntRect playerRect)
{
	

	return false;
}


// Start of 'Level' class members
Level::Level(std::string roomDirectory, std::string textureDirectory)
	: roomDirectory(roomDirectory), textureDirectory(textureDirectory)
{

}

bool Level::Init()
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

void Level::LoadRooms()
{

}

void Level::Generate()
{

}

void Level::Update(float dt)
{
	for (Room room : rooms)
	{
		room.Update(dt);
	}
}

void Level::Render(sf::RenderWindow& window)
{

}