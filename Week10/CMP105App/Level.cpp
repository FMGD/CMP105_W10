#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	tile_manager_.creatingTileMap(2);
	tile_manager_.setWindow(hwnd);

	player_manager_.setInput(in);

}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	player_manager_.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	player_manager_.update(dt);
	tile_manager_.checkCollision(*player_manager_.getPlayer());
}

// Render level
void Level::render()
{
	beginDraw();
	tile_manager_.render(); 
	player_manager_.render(window);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}