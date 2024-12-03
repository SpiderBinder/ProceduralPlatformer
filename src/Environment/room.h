
#ifndef _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_
#define _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_

#include <array>
#include <SFML/Graphics.hpp>

class Room
{
private:
	// Identification
	int id; // Unique room identification based off of position
	std::string roomType;
	sf::Vector2f position;

	// Memory
	static const int size = 32; // Preset size of rooms
	std::array<std::array<int, size>, size> tileArray;

	// Rendering tiles
	sf::Sprite sprite;

public:
	int ID() { return id; }
	sf::Vector2f getPosition() { return position; }
	std::array<std::array<int, size>, size> getTileArray() { return tileArray; }
	static const int getSize = size;
	sf::Vector2f getTileSize() { return sprite.getGlobalBounds().getSize(); }

	Room();
	Room(std::array<std::array<int, size>, size> tileArray, 
		std::string roomType);
	Room(std::array<std::array<int, size>, size> tileArray, 
		std::string roomType, 
		sf::Vector2i position);
	void update(float dt);
	void render(sf::RenderWindow& window, std::array<sf::Texture, 15> textures);
	bool withinTile(sf::Vector2f point);

};

#endif // _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_