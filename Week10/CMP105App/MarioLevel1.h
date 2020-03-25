#pragma once
#include "Framework/TileMap.h"

class MarioLevel1
{
	public:
		MarioLevel1();
		~MarioLevel1();
		void setWindow(sf::RenderWindow* hwnd);
		void render();

	private:
		TileMap tile_map_;
		sf::RenderWindow* window_;
		void creatingTileSet();
		void creatingTileMap();

	
};

