#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "Debugging/DebugBox.hpp"

void DebugBox::Position(bool active) {
	m_PositionEnabled = active;
}
void DebugBox::Scale(bool active) {
	m_ScaleEnabled = active;
}
void DebugBox::Rotation(bool active) {
	m_RotationEnabled = active;
}

DebugBox::DebugBox(std::unique_ptr<sf::Sprite>& sprite) {
	m_Rectangle = std::make_unique<sf::RectangleShape>(sprite->getGlobalBounds().size);

	m_Sprite = std::make_unique<sf::Sprite>(sprite->getTexture());

	m_Rectangle->setOrigin(m_Sprite->getOrigin());
	m_Rectangle->setPosition(m_Position);

	m_Rectangle->setOutlineColor(sf::Color::Red);
	m_Rectangle->setFillColor(sf::Color::Transparent);
	m_Rectangle->setOutlineThickness(2);

	setPosition(m_Sprite->getPosition());
}

DebugBox::DebugBox(sf::Vector2f size, sf::Vector2f position) {
	m_Rectangle = std::make_unique<sf::RectangleShape>(size);

	m_Rectangle->setPosition(position);
	m_Rectangle->setOutlineColor(sf::Color::Red);
	m_Rectangle->setFillColor(sf::Color::Transparent);
	m_Rectangle->setOutlineThickness(2);

	setPosition(position);
}


std::expected<sf::Sprite, bool> DebugBox::GetSprite() {
	if(m_Sprite != nullptr) {
		return *m_Sprite;
	}
	else {
		return std::unexpected(false);
	}
}

void DebugBox::setPosition(sf::Vector2f position) {
	m_Position = position;
}

void DebugBox::Update() {
	if (GetSprite()) {
		std::cout << "UPDATING!" << std::endl;
		if (m_PositionEnabled) {
			m_Rectangle->setPosition(m_Position); // Set position
			setPosition(m_Sprite->getPosition()); // Update position
		}
		
		if (m_RotationEnabled) {
			m_Rectangle->setRotation(m_Sprite->getRotation());
		}
		
		if (m_ScaleEnabled) {
			m_Rectangle->setSize(m_Sprite->getGlobalBounds().size);
		}
		
		return;
	}

	// Will only work if we have a position and no sprite
	if (m_PositionEnabled) {
		m_Rectangle->setPosition(m_Position); // Set position
	}
}