#pragma once
#include "Framework/TileMap.h"
#include "Framework/Collision.h"

class TileManager
{
	public:
		TileManager();
		~TileManager();
		void setWindow(sf::RenderWindow* hwnd);
		void render();
		void checkCollision(GameObject& game_object);
		void creatingTileMap(int map_code);

	private:
		TileMap tile_map_;
		sf::RenderWindow* window_;
		void creatingTileSet();
	
};

