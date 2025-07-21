#include <Game/Bird.hpp>
#include <iostream>
#include <algorithm>

#include "Game/Config/BirdConfig.hpp"
#include "Debugging/DebugBox.hpp"

Bird::Bird(float gravity) {
	m_Texture.loadFromFile("assets/images/Bird.png");

	// Create the sprite
	m_Sprite = std::make_unique<sf::Sprite>(m_Texture);
	// Set the origin at exactly the middle left side of the sprite. Used for the tilting when flapping
	m_Sprite->setOrigin({ m_Sprite->getGlobalBounds().size.x / 2, m_Sprite->getGlobalBounds().size.y / 2 });
	m_Sprite->setPosition({ 200, 150 });

	// Create the actual collision part of the sprite
	sf::Vector2f collision_box_position = sf::Vector2f(0,0);
	sf::Vector2f collision_box_size(BirdConfig::dim_BirdTextureX, BirdConfig::dim_BirdTextureY);

	m_CollisionBox = std::make_unique<sf::RectangleShape>(collision_box_size);
	m_CollisionBox->setPosition(collision_box_position);
	
	m_CollisionBox->setOrigin(m_Sprite->getOrigin()); // Update the origin of the collision box too

	m_Gravity = gravity;
	m_Velocity = 0;


	// DEBUG SECTION
	if (debug_mode) {
		debug_CollisionBox = std::make_unique<DebugBox>(m_CollisionBox->getSize(), m_CollisionBox->getPosition());
		debug_CollisionBox->GetBox().setOrigin(m_CollisionBox->getOrigin());
	}
}

void Bird::Draw(sf::RenderWindow& window) {
	window.draw(*m_Sprite);

	// DEBUG SECTION
	if (debug_mode) {
		window.draw(debug_CollisionBox->GetBox());
	}
}

void Bird::Flap() {
	if (m_Dead) return;
	if (!m_ControlsEnabled) return;

	if (sf::Keyboard::isKeyPressed(BirdConfig::FlapKey)) {
		// Reset velocity
		m_Velocity = 0;
		// Apply upward force
		m_Velocity += BirdConfig::UpwardForce;
	}
}

void Bird::Update(float dt) {
	// Apply gravity
	m_Velocity += m_Gravity * dt;
	m_Sprite->move({ 0, -m_Velocity });

	// Set the rotation
	sf::Angle rotation = sf::degrees(-m_Velocity * 2);
	rotation = std::clamp(rotation, BirdConfig::MinimumAngle, BirdConfig::MaximumAngle);

	m_Sprite->setRotation(rotation);

	// Update the collision box
	sf::Vector2f x_offset(m_Sprite->getGlobalBounds().size.x / 4, 0);
	sf::Vector2f y_offset(0, m_Sprite->getGlobalBounds().size.y / 4);
	m_CollisionBox->setPosition(m_Sprite->getPosition() + x_offset + y_offset);
	m_CollisionBox->setRotation(m_Sprite->getRotation());
	// DEBUG SECTION
	if (debug_mode) {
		debug_CollisionBox->GetBox().setRotation(m_CollisionBox->getRotation());
		debug_CollisionBox->setPosition(m_CollisionBox->getPosition());
		debug_CollisionBox->Update();
	}
}

void Bird::Die() {
	DisableControls();
	m_Dead = true;

	std::cout << "You died!" << std::endl;
}

void Bird::DisableControls() {
	m_ControlsEnabled = false;
}