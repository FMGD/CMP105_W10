#include "Player.h"

// Constructor
Player::Player()
{
	// Initialise gravity value (gravity 9.8, 200 scale, 200 px/s this will need to be uniform)
	scale_ = 10.0f;
	gravity_ = sf::Vector2f(0, 9.8f) *scale_;
	velocity = sf::Vector2f(0.f, 0.f) *scale_;

	jump_vector_ = sf::Vector2f(0, -10.0f)*scale_;
	is_jumping_ = false;
	is_ducking_ = false;


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
		
		if (!is_jumping_ && !is_ducking_)
		{
			velocity = jump_vector_;
			is_jumping_ = true;
			current_animation_ = &swim_;
			animate_ = true;
		}
		else if (is_ducking_) // get up
		{
			setCollisionBox(2, 1, 27, 40);
			current_animation_ = &walk_;
			animate_ = true;
		}


	}
	else if (input->isKeyDown(sf::Keyboard::S)) //Duck
	{
		//input->setKeyUp(sf::Keyboard::S);

		setCollisionBox(2, 15.f, 27, 28.f);
		is_ducking_ = true;	
		current_animation_ = &duck_;
	}

	if (input->isKeyDown(sf::Keyboard::A)) //Walk left
	{
		//input->setKeyUp(sf::Keyboard::A);

		move(-80.f * dt, 0 * dt);

		if (!is_ducking_)
		{
			setCollisionBox(2, 1, 27, 40);

			if (walk_.getFlipped() == false) walk_.setFlipped(true); // Flipped to left
			current_animation_ = &walk_;
			animate_ = true;
		}
		else
		{
			if (duck_.getFlipped() == false) duck_.setFlipped(true); // Flipped to left
		}
	}
	else if (input->isKeyDown(sf::Keyboard::D)) //Walk right
	{
		//input->setKeyUp(sf::Keyboard::D);

		move(80.f * dt, 0 * dt);

		if (!is_ducking_)
		{
			setCollisionBox(2, 1, 27, 40);

			if (walk_.getFlipped() == true) walk_.setFlipped(false);  // Not Flipped to left
			current_animation_ = &walk_;
			animate_ = true;
		}
		else
		{
			if (duck_.getFlipped() == true) duck_.setFlipped(false);  // Not Flipped to left
		}
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
	sf::Vector2f displacement = (velocity * dt) + (0.5f * gravity_ * dt * dt); // s = ut + 1/2*a*t^2
	velocity += gravity_ * dt;  // v = u + at
	setPosition(getPosition().x, getPosition().y + displacement.y); // Only we want to move it in 'y' direction
}

void Player::collisionResponse(GameObject* collider)
{
	// Calculate de difference between the middle point of the player and the middle point of the collider
	// It has been taken into account as initial point (the player), and the final point (the collider)
	// Difference =  Final point - Initial point
	sf::Vector2f diffMiddlePointCollisionBoxes = sf::Vector2f(collider->getCollisionBox().left + collider->getCollisionBox().width/2, collider->getCollisionBox().top + getCollisionBox().height/2) -
		sf::Vector2f(getCollisionBox().left + getCollisionBox().width/2, getCollisionBox().top + getCollisionBox().height/2 );

	sf::Vector2f diffPlayerCollisionBoxAndSizeLeftTop = sf::Vector2f(abs(getCollisionBox().left - getPosition().x), abs(getCollisionBox().top - getPosition().y));
	sf::Vector2f diffPlayerCollisionBoxAndSizeRightBottom = sf::Vector2f(abs((getPosition().x + getSize().x) - (getCollisionBox().left + getCollisionBox().width)), 
				abs((getPosition().y + getSize().y) - (getCollisionBox().top + getCollisionBox().height)));

	// Collision with X-axis (Horizontal)
	//##########################################################
	// This needs to be absolute values. because based on player position these values can be positive or negative.
	if (abs(diffMiddlePointCollisionBoxes.x) < abs(diffMiddlePointCollisionBoxes.y))
	{	
		velocity.y = 0;

		if (is_jumping_)
		{
			is_jumping_ = false;
			current_animation_ = &walk_;
			animate_ = true;
		}

		// When there is a collision on the BOTTOM side of the player (Player is on the above the collider)
		if (diffMiddlePointCollisionBoxes.y > 0)
		{
			//setPosition(getPosition().x, collider->getCollisionBox().top - getSize().y + diffPlayerCollisionBoxAndSizeRightBottom.y );
			//std::cout << "Collision Response X - Detected on the bottom side of the player" << std::endl;
		}
		else // When there is a collision on the TOP side of the player (Player is on the under the collider)
		{
			setPosition(getPosition().x, collider->getCollisionBox().top + collider->getCollisionBox().height - diffPlayerCollisionBoxAndSizeLeftTop.y);
			std::cout << "Collision Response X - Detected on the top side of the player" << std::endl;
		}
		//std::cout << "Collision Response X" << std::endl;

	}
	/*else // Collissions with Y-axis (Vertical)
	{
		velocity.x = 0;

		// When there is a collision on the RIGHT side of the player (Player is on the left side of the collider)
		if (diffMiddlePointCollisionBoxes.x > 0)
		{
			setPosition(collider->getPosition().x - getSize().x + diffPlayerCollisionBoxAndSizeRightBottom.x, getPosition().y);
			std::cout << "Collision Response Y - Detected on the right side of the player" << std::endl;
		}
		else // When there is a collision on the LEFT side of the player (Player is on the right side of the collider)
		{
			setPosition( (collider->getPosition().x + collider->getSize().x) - diffPlayerCollisionBoxAndSizeLeftTop.x , getPosition().y);
			std::cout << "Collision Response Y - Detected on the left side of the player" << std::endl;
		}
		//std::cout << "Collision Response Y" << std::endl;
	}*/

}