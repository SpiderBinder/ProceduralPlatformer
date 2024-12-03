

#ifndef _PROCEDURALPLATFORMER_ENVIRONMENT_LEVEL_H_
#define _PROCEDURALPLATFORMER_ENVIRONMENT_LEVEL_H_

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "room.h"

class Level
{
private:
	std::string roomDirectory;
	std::vector<Room> roomPresets;

	std::string textureDirectory;
	std::array<std::string, 15> textureNames;
	std::array<sf::Texture, 15> textures;

	std::vector<Room> rooms;
	std::vector<Room> loadedRooms;

	void loadRooms();
	void generate(/*int seed*/);

public:
	Level(std::string directory);
	bool init();
	void update(float dt);
	void render(sf::RenderWindow& window);
	bool collisionDetect(sf::FloatRect collider);

};

#endif // _PROCEDURALPLATFORMER_ENVIRONMENT_LEVEL_H_