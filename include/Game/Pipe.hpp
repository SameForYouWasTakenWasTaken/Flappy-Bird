#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "Bird.hpp"

class Pipe {
public:
	bool isExpired = false;

	Pipe(sf::RenderWindow& window);
	Pipe(sf::RenderWindow& window, std::unique_ptr<Pipe>& otherPipe);
	void Draw(sf::RenderWindow& window);
	void Update(float dt);
	void checkCollision(std::unique_ptr<Bird>& bird);
	sf::Sprite& getSprite() { return *m_Sprite; }

private:

	sf::Texture m_Texture;

	std::unique_ptr<sf::Sprite> m_Sprite;
	std::unique_ptr<sf::Clock> m_CurrentLifeTime;

	// DEBUG SECTION
	const bool debug_mode = false;
	std::unique_ptr<sf::RectangleShape> debug_CollisionBox;
	std::unique_ptr<sf::RectangleShape> debug_SpriteBoundingBox;
};

struct PipeGroup {
	std::unique_ptr<Pipe> topPipe;
	std::unique_ptr<Pipe> bottomPipe;
};