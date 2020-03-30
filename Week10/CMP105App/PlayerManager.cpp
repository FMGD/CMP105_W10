#include "PlayerManager.h"

// Constructor
PlayerManager::PlayerManager()
{
	spawn_point_ = sf::Vector2f(0, 350);
	texture_.loadFromFile("gfx/MarioSheetT.png");

	player_.setPosition(spawn_point_);
	player_.setAlive(false);
	player_.setTexture(&texture_);
	player_.setSize(sf::Vector2f(15 * 2, 21 * 2));

	player_.setCollisionBox(0, 0, player_.getSize().x, player_.getSize().y);
	player_.setOutlineColor(sf::Color::Green); // For collision box
	player_.setOutlineThickness(2.f);

}

// Destructor
PlayerManager::~PlayerManager()
{
}

// Functions
void PlayerManager::update(float dt)
{
	player_.update(dt);
}

void PlayerManager::render(sf::RenderWindow* window)
{
	window->draw(player_);
}

void PlayerManager::handleInput(float dt)
{
	player_.handleInput(dt);
}

void PlayerManager::setInput(Input* in)
{
	player_.setInput(in);
}

GameObject* PlayerManager::getPlayer()
{
	return &player_;
}

