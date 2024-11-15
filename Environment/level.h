
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

// NOTE: Currently unused
//class Tile
//{
//private:
//	bool collision;
//	int tileType;
//
//public:
//	bool Collision() { return collision; }
//
//	Tile(int type);
//	void Update();
//};

class Room
{
private:
	// Identification
	int id;
	sf::Vector2i position;

	// Memory
	static const int size = 16; // Preset size of rooms
	std::array<std::array<int, size>, size> tileArray; // NOTE: Temporary int instead of 'Tile'

	// Rendering tiles
	sf::Sprite sprite;
	sf::Texture textures[15];

public:
	int ID() { return id; }
	static const int Size = size;

	Room(std::array<std::array<int, size>, size> tileArray);
	void Update(float dt);
	void Render(sf::RenderWindow& window, sf::Texture textures[15]);
	bool CollisionDetect(sf::IntRect playerRect);
	
};

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
	bool Init();
	void Generate(/*int seed*/);
	void LoadRooms();
	void Update(float dt);
	void Render(sf::RenderWindow& window);

};