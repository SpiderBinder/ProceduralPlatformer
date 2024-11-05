#include <iostream>
#include <SFML/Graphics.hpp>

class Level
{
private:
	//std::vector<Chunk> chunks;

public:
	bool Init(int seed);
	void Update();
	void Render(sf::RenderWindow& window);

};

class Chunk
{
private:
	
};

class Tile
{

};