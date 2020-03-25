#include "MarioLevel1.h"

MarioLevel1::MarioLevel1()
{
	// Loading the texture
	tile_map_.loadTexture("gfx/marioTiles.png");

	creatingTileSet();

	creatingTileMap();

}

MarioLevel1::~MarioLevel1()
{

}

void MarioLevel1::creatingTileSet()
{
	// Creating the TitleSet
	GameObject tile;
	std::vector<GameObject> tile_set;
	int num_total_tiles = 7;

	for (int i = 0; i < num_total_tiles; i++)
	{
		// Set title
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);

		//Add to collection of tiles
		tile_set.push_back(tile);
	}

	tile_set[0].setCollider(false);
	tile_set[0].setTextureRect(sf::IntRect(187, 51, 16, 16)); //Sky

	tile_set[1].setTextureRect(sf::IntRect(0, 0, 16, 16));
	tile_set[2].setTextureRect(sf::IntRect(17, 0, 16, 16));
	tile_set[3].setTextureRect(sf::IntRect(34, 0, 16, 16));
	tile_set[4].setTextureRect(sf::IntRect(0, 34, 16, 16));
	tile_set[5].setTextureRect(sf::IntRect(17, 34, 16, 16));
	tile_set[6].setTextureRect(sf::IntRect(34, 34, 16, 16));

	tile_map_.setTileSet(tile_set);
}

void MarioLevel1::creatingTileMap()
{

	// Map dimensions
	sf::Vector2u map_size(10, 6);

	// Build map
	std::vector<int> map =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 3, 0, 0, 0, 0, 0,
		1, 2, 3, 4, 6, 1, 2, 3, 0, 0,
		4, 5, 6, 0, 0, 4, 5, 6, 0, 0,
	};

	tile_map_.setTileMap(map, map_size);

	tile_map_.setPosition(sf::Vector2f(0, 408));
	tile_map_.buildLevel();

}

void MarioLevel1::setWindow(sf::RenderWindow* hwnd)
{
	window_ = hwnd;
}

void MarioLevel1::render()
{
	tile_map_.render(window_);
}