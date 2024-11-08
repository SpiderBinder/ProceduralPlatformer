#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Tile
{
private:
	bool collision;
	int tileType;

public:

	Tile(int type);
	void Update();
};

class Room
{
private:
	// Identification
	int ID;

	// Memory
	static const int size = 16; // Preset size of rooms
	Tile tileArray[size][size];

	// Rendering tiles
	sf::Sprite sprite;

public:
	int Size() { return size; }

	Room(int arrayInput[size][size]);
	void Update(float dt);
	void Render(sf::Texture textures[15]);
	
	bool CollisionDetect();
	
};

class Level
{
private:
	std::vector<Room> rooms;

public:
	Level();
	bool Init();
	void Generate(/*int seed*/);
	void LoadRoom();
	void Update(float dt);
	void Render(sf::RenderWindow& window);

};

// Test Comment