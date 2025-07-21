#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "Debugging/DebugBox.hpp"


class Bird {
public:
	Bird(float gravity);
	~Bird() {
		std::cout << "Bird destroyed" << std::endl;
	}
	void Draw(sf::RenderWindow& window); // Draw the bird to the screen
	void Update(float dt); // Update the bird (position, size, etc) based on delta time
	void Flap(); //'key' will be checked if it is m_FlapKey.
	void DisableControls();
	void Die();
	
	bool IsDead() const { return m_Dead; }
	sf::Sprite& getSprite() { return *m_Sprite; } // Get the sprite
	sf::RectangleShape& getCollisionBox() const { return *m_CollisionBox; } // Get the collision box
private:
	sf::Texture m_Texture;
	
	std::unique_ptr<sf::Sprite> m_Sprite; // The actual sprite texture gets constructed in the Bird constructor.
	std::unique_ptr<sf::RectangleShape> m_CollisionBox;
	
	float m_Gravity;
	float m_Velocity; // This is only the Y velocity

	bool m_ControlsEnabled = true;
	bool m_Dead = false;

	// DEBUG SECTION

	const bool debug_mode = false;
	std::unique_ptr<DebugBox> debug_CollisionBox;
	std::unique_ptr<DebugBox> debug_SpriteBoundingBox;
};