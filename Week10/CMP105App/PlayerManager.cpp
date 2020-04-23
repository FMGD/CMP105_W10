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

	player_.setCollisionBox(2, 1, 27, 40);

	updateCollisionBoxShape();
	collision_box_player_shape_.setFillColor(sf::Color::Transparent);
	collision_box_player_shape_.setOutlineColor(sf::Color::Green);
	collision_box_player_shape_.setOutlineThickness(2.f);
}

// Destructor
PlayerManager::~PlayerManager()
{
}

// Functions
void PlayerManager::update(float dt)
{
	player_.update(dt);
	updateCollisionBoxShape();
}

void PlayerManager::render(sf::RenderWindow* window)
{
	window->draw(player_);
	window->draw(collision_box_player_shape_);
}

void PlayerManager::handleInput(float dt)
{
	player_.handleInput(dt);
}

void PlayerManager::setInput(Input* in)
{
	player_.setInput(in);
}

void PlayerManager::updateCollisionBoxShape()
{
	collision_box_player_shape_.setSize(sf::Vector2f(player_.getCollisionBox().width, player_.getCollisionBox().height));
	collision_box_player_shape_.setPosition(sf::Vector2f(player_.getCollisionBox().left, player_.getCollisionBox().top));
}

GameObject* PlayerManager::getPlayer()
{
	return &player_;
}

