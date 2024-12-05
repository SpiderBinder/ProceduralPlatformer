
#ifndef _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_
#define _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_

#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>

class Room
{
public: 
	// TODO: Increase tile size and sprite size by a factor of 2
	static const int Size = 8; // Preset size of rooms
	static const int TileSize = 32; // Preset size of tiles

private:
	// Identification
	int id; // Unique room identification based off of global position
	std::string roomType;
	sf::Vector2f position;

	std::array<std::array<int, Size>, Size> tileArray;

	// Rendering tiles
	sf::Sprite sprite;

public:
	int ID() { return id; }
	sf::Vector2f getPosition() { return position; }
	std::array<std::array<int, Size>, Size> getTileArray() { return tileArray; }

	Room();
	Room(std::array<std::array<int, Size>, Size> tileArray, 
		std::string roomType);
	Room(std::array<std::array<int, Size>, Size> tileArray, 
		std::string roomType, 
		sf::Vector2f position);
	void update(float dt);
	void render(sf::RenderWindow& window, std::vector<sf::Texture> textures);
	
	bool withinTile(sf::Vector2f point);

};

#endif // _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_