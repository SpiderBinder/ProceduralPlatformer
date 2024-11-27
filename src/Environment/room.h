
#ifndef _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_
#define _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_

#include <array>
#include <SFML/Graphics.hpp>

class Room
{
private:
	// Identification
	int id;
	std::string roomType;
	sf::Vector2i position;

	// Memory
	static const int size = 16; // Preset size of rooms
	std::array<std::array<int, size>, size> tileArray;

	// Rendering tiles
	sf::Sprite sprite;
	sf::Texture textures[15];

public:
	int ID() { return id; }
	std::array<std::array<int, size>, size> layout() { return tileArray; }
	static const int Size = size;

	Room();
	Room(std::array<std::array<int, size>, size> tileArray, 
		std::string roomType);
	Room(std::array<std::array<int, size>, size> tileArray, 
		std::string roomType, 
		sf::Vector2i position);
	void update(float dt);
	void render(sf::RenderWindow& window, sf::Texture textures[15]);

};

#endif // _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_