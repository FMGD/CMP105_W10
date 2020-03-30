#include "TileManager.h"

TileManager::TileManager()
{
	// Loading the texture
	tile_map_.loadTexture("gfx/marioTiles.png");

	creatingTileSet();

	//creatingTileMap();

}

TileManager::~TileManager()
{

}

void TileManager::creatingTileSet()
{
	// Creating the TitleSet
	GameObject tile;
	std::vector<GameObject> tile_set;
	int num_total_tiles = 7;

	for (int i = 0; i < num_total_tiles; i++)
	{
		// Set title
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, tile.getSize().x, tile.getSize().y);
		tile.setOutlineColor(sf::Color::Red); // For collision box
		tile.setOutlineThickness(2.f);
		tile.setCollider(true);

		//Add to collection of tiles
		tile_set.push_back(tile);
	}

	tile_set[0].setCollider(false);
	tile_set[0].setTextureRect(sf::IntRect(187, 51, 16, 16)); //Sky / empty

	tile_set[1].setTextureRect(sf::IntRect(0, 0, 16, 16)); // Left corner (ground with grass)
	tile_set[2].setTextureRect(sf::IntRect(17, 0, 16, 16)); // Middle (ground with grass)
	tile_set[3].setTextureRect(sf::IntRect(34, 0, 16, 16)); // Right corner (ground with grass)

	tile_set[4].setTextureRect(sf::IntRect(0, 34, 16, 16)); // left ground
	tile_set[5].setTextureRect(sf::IntRect(17, 34, 16, 16)); // middle ground
	tile_set[6].setTextureRect(sf::IntRect(34, 34, 16, 16)); // right ground

	tile_map_.setTileSet(tile_set);
}

void TileManager::creatingTileMap(int map_code = 1)
{

	// Map dimensions
	sf::Vector2u map_size(10, 6);
	std::vector<int> map;

	// Build map
	if (map_code == 1)
	{
		map =
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 1, 3, 0, 0, 0, 0, 0,
			1, 2, 3, 4, 6, 1, 2, 3, 0, 0,
			4, 5, 6, 0, 0, 4, 5, 6, 0, 0,
		};
	}
	else
	{
		map =
		{
			1, 3, 0, 0, 0, 0, 0, 0, 0, 0,
			4, 6, 0, 1, 0, 0, 0, 0, 0, 1,
			0, 0, 0, 0, 1, 3, 0, 0, 0, 4,
			0, 0, 1, 3, 4, 6, 1, 3, 0, 0,
			0, 0, 4, 6, 0, 0, 4, 6, 1, 3,
			0, 0, 0, 0, 0, 0, 0, 0, 4, 6,
		};
	}

	tile_map_.setTileMap(map, map_size);

	tile_map_.setPosition(sf::Vector2f(0, 408));
	tile_map_.buildLevel();


}

void TileManager::setWindow(sf::RenderWindow* hwnd)
{
	window_ = hwnd;
}

void TileManager::render()
{
	tile_map_.render(window_);
}

void TileManager::checkCollision(GameObject& game_object)
{
	std::vector<GameObject>* world = tile_map_.getLevel(); // Pointer to level assests

	for (int i = 0; i < (int)world->size(); i++)
	{
		// if collision check should occur
		if ((*world)[i].isCollider())
		{
			if (Collision::checkBoundingBox(&game_object, &(*world)[i]))
			{
				game_object.collisionResponse(&(*world)[i]); // We pass as parameter the tile object 
			}
		}
	}
}
