

#ifndef _PROCEDURALPLATFORMER_ENVIRONMENT_LEVEL_H_
#define _PROCEDURALPLATFORMER_ENVIRONMENT_LEVEL_H_

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "room.h"

class Level
{
private:
	const std::string roomDirectory;
	std::vector<Room> roomPresets;

	const std::string textureDirectory;
	const std::string textureNames[15];
	sf::Texture textures[15];

	std::vector<Room> rooms;

public:
	Level(std::string roomDirectory, std::string textureDirectory);
	bool init();
	void generate(/*int seed*/);
	void loadRooms();
	void update(float dt);
	void render(sf::RenderWindow& window);

};

#endif // _PROCEDURALPLATFORMER_ENVIRONMENT_LEVEL_H_