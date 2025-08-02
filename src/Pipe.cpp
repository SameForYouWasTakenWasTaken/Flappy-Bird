#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <random>
#include <algorithm>

#include "Game/Pipe.hpp"
#include "Game/Config/PipeConfig.hpp"


// Thank you stack overflow :)
template<typename T>
int RandomNumber(T a, T b) {
	if (a > b) std::swap(a, b);
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<> dist(static_cast<int>(a), static_cast<int>(b));

	return dist(rng);
}
Pipe::Pipe(const sf::RenderWindow& window) {
	m_Texture.loadFromFile("assets/images/Pipe.png");

	m_Sprite = std::make_unique<sf::Sprite>(m_Texture);
	m_CurrentLifeTime = std::make_unique<sf::Clock>();

	sf::Vector2u windowSize = window.getSize();
	const float offset = PipeConfig::bottom_XPipeSpawnOffset;

	float spriteRightPosition = static_cast<float>(windowSize.x) - m_Sprite->getGlobalBounds().size.x + offset;

	auto height = static_cast<float>(RandomNumber(PipeConfig::bottom_MinimumPipeSpawnHeight,
	                                               PipeConfig::bottom_MaximumPipeSpawnHeight));

	m_Sprite->setPosition({ spriteRightPosition, height });
	m_CurrentLifeTime->start();

	// DEBUG SECTION
	if (debug_mode) {
		if (debug_mode) {
			debug_CollisionBox = std::make_unique<sf::RectangleShape>(m_Sprite->getGlobalBounds().size);
			debug_CollisionBox->setFillColor(sf::Color::Transparent);
			debug_CollisionBox->setOutlineColor(sf::Color::Red);
			debug_CollisionBox->setOutlineThickness(2);

			debug_SpriteBoundingBox = std::make_unique<sf::RectangleShape>(m_Sprite->getGlobalBounds().size);
			debug_SpriteBoundingBox->setOutlineColor(sf::Color::Green);
			debug_SpriteBoundingBox->setFillColor(sf::Color::Transparent);
			debug_SpriteBoundingBox->setOutlineThickness(2);
		}
	}
}

Pipe::Pipe(sf::RenderWindow& window, const std::unique_ptr<Pipe>& otherPipe){
	m_Texture.loadFromFile("assets/images/Pipe.png");

	m_CurrentLifeTime = std::make_unique<sf::Clock>();
	m_Sprite = std::make_unique<sf::Sprite>(m_Texture);

	sf::Vector2f otherPipe_Position = otherPipe->getSprite().getPosition();
	float spriteRightPosition = otherPipe_Position.x;


	float offset = PipeConfig::top_PipeSpawnOffset;
	float pipe_height = otherPipe_Position.y + m_Sprite->getScale().y + offset;


	m_Sprite->setOrigin({ m_Sprite->getGlobalBounds().size.x, m_Sprite->getGlobalBounds().size.y / 2 });

	m_Sprite->setRotation(sf::degrees(180));
	m_Sprite->setPosition({ spriteRightPosition, pipe_height});


	m_CurrentLifeTime->start();

	// DEBUG SECTION
	if (debug_mode) {
		if (debug_mode) {
			debug_CollisionBox = std::make_unique<sf::RectangleShape>(m_Sprite->getGlobalBounds().size);
			debug_CollisionBox->setFillColor(sf::Color::Transparent);
			debug_CollisionBox->setOutlineColor(sf::Color::Red);
			debug_CollisionBox->setOutlineThickness(2);

			debug_SpriteBoundingBox = std::make_unique<sf::RectangleShape>(m_Sprite->getLocalBounds().size);
			debug_SpriteBoundingBox->setOutlineColor(sf::Color::Green);
			debug_SpriteBoundingBox->setFillColor(sf::Color::Transparent);
			debug_SpriteBoundingBox->setOutlineThickness(2);
		}
	}
}

void Pipe::checkCollision(const std::unique_ptr<Bird>& bird) const {
	if (!bird->IsDead() && m_Sprite != nullptr) {
		sf::FloatRect bird_bounds = bird->getCollisionBox().getGlobalBounds();
		sf::FloatRect pipe_bounds = m_Sprite->getGlobalBounds();

		if (bird_bounds.findIntersection(pipe_bounds)) {
			bird->Die();
		}
	}
}

void Pipe::Draw(sf::RenderWindow& window) const {
	window.draw(*m_Sprite);

	// DEBUG SECTION
	if (debug_mode) {
		window.draw(*debug_CollisionBox);
		//window.draw(*debug_SpriteBoundingBox);
	}
}

void Pipe::Update(float dt) {
	m_Sprite->move({-PipeConfig::PipeSpeed * dt, 0});
	if (m_CurrentLifeTime->getElapsedTime().asSeconds() >= PipeConfig::PipeLifeTime) {
		m_CurrentLifeTime->stop();
		isExpired = true;
	}

	// DEBUG SECTION
	if (debug_mode) {
		debug_CollisionBox->setPosition(m_Sprite->getPosition());
		debug_SpriteBoundingBox->setPosition(m_Sprite->getPosition());
	}
}

