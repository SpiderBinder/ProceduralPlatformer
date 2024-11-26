
#ifndef _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_
#define _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_

#include <array>
#include <SFML/Graphics.hpp>

class Room
{
private:
	// Identification
	int id;
	sf::Vector2i position;

	// Memory
	static const int size = 16; // Preset size of rooms
	std::array<std::array<int, size>, size> tileArray;

	// Rendering tiles
	sf::Sprite sprite;
	sf::Texture textures[15];

public:
	int ID() { return id; }
	static const int Size = size;

	Room(std::array<std::array<int, size>, size> tileArray);
	void update(float dt);
	void render(sf::RenderWindow& window, sf::Texture textures[15]);
	bool collisionDetect(sf::IntRect playerRect);

};

#endif // _PROCEDURALPLATFORMER_ENVIRONMENT_ROOM_H_