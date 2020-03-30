#pragma once
#include "Player.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

class PlayerManager
{

private:
	Player player_;
	sf::Vector2f spawn_point_;
	sf::Texture texture_;


public:
	PlayerManager();
	~PlayerManager();

	GameObject* getPlayer();
	void setInput(Input* in);
	void handleInput(float dt);
	void update(float dt);
	void render(sf::RenderWindow* window);


};
