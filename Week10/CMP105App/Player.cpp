#include "Player.h"

// Constructor
Player::Player()
{
	// Initialise gravity value (gravity 9.8, 200 scale, 200 px/s this will need to be uniform)
	scale_ = 200.0f;
	gravity_ = sf::Vector2f(0, 9.8f) * scale_;
	velocity = sf::Vector2f(80.f, 80.f) * scale_;

	jump_vector_ = sf::Vector2f(0, -2.0f) * scale_;
	is_jumping_ = false;


	//Setup walk_ animation
	walk_.addFrame(sf::IntRect(0, 0, 15, 21));
	walk_.addFrame(sf::IntRect(15, 0, 15, 21));
	walk_.addFrame(sf::IntRect(30, 0, 15, 21));
	walk_.addFrame(sf::IntRect(45, 0, 15, 21));
	walk_.setFrameSpeed(1.f / 10.f);

	//Setup swim_ animation
	swim_.addFrame(sf::IntRect(0, 21, 16, 20));
	swim_.addFrame(sf::IntRect(16, 21, 16, 20));
	swim_.addFrame(sf::IntRect(32, 21, 16, 20));
	swim_.setFrameSpeed(1.f / 10.f);

	//Setup duck_ animation
	duck_.addFrame(sf::IntRect(0, 41, 16, 20));
	duck_.addFrame(sf::IntRect(16, 41, 16, 20));
	duck_.setFrameSpeed(1.f / 10.f);

	//Set current animations
	current_animation_ = &walk_;
	setTextureRect(current_animation_->getCurrentFrame());
	animate_ = false;

}

// Destructor
Player::~Player()
{

}

// Functions
void Player::update(float dt)
{
	applyGravityForce(dt);

	if (animate_)
	{
		current_animation_->animate(dt);
		setTextureRect(current_animation_->getCurrentFrame());
	}

}

void Player::handleInput(float dt)
{

	if (input->isKeyDown(sf::Keyboard::W)) //Jump
	{

		if (!is_jumping_)
		{
			velocity = jump_vector_;
			is_jumping_ = true;
		}

		current_animation_ = &swim_;
		animate_ = true;
	}
	else if (input->isKeyDown(sf::Keyboard::S)) //Duck
	{
		//setCollisionBox(0, getSize().y - getCollisionBox().height/2, getCollisionBox().width, getCollisionBox().height / 2); // TODO - Here I change the size of the collision box
		current_animation_ = &duck_;
		//move(0 * dt, velocity.y * dt);
		//animate_ = true;
	}

	if (input->isKeyDown(sf::Keyboard::A)) //Walk left
	{
		velocity.x = 80.f;
		if (walk_.getFlipped() == false) walk_.setFlipped(true); // Flipped to left
		move(-velocity.x * dt, 0 * dt);
		current_animation_ = &walk_;
		animate_ = true;
	}
	else if (input->isKeyDown(sf::Keyboard::D)) //Walk right
	{
		velocity.x = 80.f;
		if (walk_.getFlipped() == true) walk_.setFlipped(false);  // Not Flipped to left
		move(velocity.x * dt, 0 * dt);
		current_animation_ = &walk_;
		animate_ = true;
	}

	if (!input->isKeyDown(sf::Keyboard::W) && !input->isKeyDown(sf::Keyboard::S) && //If the player is stopped then reset animation
		!input->isKeyDown(sf::Keyboard::A) && !input->isKeyDown(sf::Keyboard::D))
	{
		setTextureRect(current_animation_->getCurrentFrame());
		current_animation_->reset();
		animate_ = false;

	}

}

// Apply gravity force: increasing velocity
// Move shape by new velocity
void Player::applyGravityForce(float dt)
{
	sf::Vector2f displacement = velocity * dt + 0.5f * gravity_ * dt * dt; // s = ut + 1/2*a*t^2
	velocity += gravity_ * dt;  // v = u + at
	setPosition(getPosition().x, getPosition().y + displacement.y); // Only we want to move it in 'y' direction
}

void Player::collisionResponse(GameObject* collider)
{
	// Calculate de difference between the middle point of the player and the middle point of the collider
	// It has been taken into account as initial point (the player), and the final point (the collider)
	// Difference =  Final point - Initial point
	sf::Vector2f diff = (collider->getPosition() + sf::Vector2f(collider->getSize().x/2, collider->getSize().y/2)) -
		(getPosition() + sf::Vector2f(getSize().x/2, getSize().y/2) );

	// Collision with X-axis (Horizontal)
	if (abs(diff.x) < abs(diff.y))
	{	
		velocity.y = 0;

		if (is_jumping_)
		{
			is_jumping_ = false;
			current_animation_ = &walk_;
			animate_ = true;
		}

		// Player is above the collider
		if (diff.y > 0)
		{
			setPosition(getPosition().x, collider->getPosition().y - getSize().y);
		}
		else // Player is under the collider
		{
			setPosition(getPosition().x, collider->getPosition().y + collider->getSize().y);
		}
		//std::cout << "Collision Response X" << std::endl;

	}
	else // Collissions with Y-axis (Vertical)
	{
		velocity.x = 0;

		// Player is on the Left side of the collider
		if (diff.x > 0)
		{
			setPosition(collider->getPosition().x - getSize().x, getPosition().y);
		}
		else // Player is on the Right side of the collider
		{
			setPosition(collider->getPosition().x + collider->getSize().x, getPosition().y);
		}
		//std::cout << "Collision Response Y" << std::endl;
	}

}