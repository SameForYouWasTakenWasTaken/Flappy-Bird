#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <expected>

class DebugBox {
public:
	DebugBox(std::unique_ptr<sf::Sprite>& sprite);
	DebugBox(sf::Vector2f size, sf::Vector2f position);

	void Position(bool active); // Automatically position relative to the object (DEFAULT ON)
	void Rotation(bool active); // Automatically rotate relative to the object (DEFAULT ON, SPRITE NEEDED)
	void Scale(bool active); // Automatically scale relative to the object (DEFAULT ON, SPRITE NEEDED)

	void Update();

	void setPosition(sf::Vector2f position);

	sf::RectangleShape& GetBox() { return *m_Rectangle; } // Returns the box object
	std::expected<sf::Sprite, bool> GetSprite(); // Returns the sprite object, if it doesn't
private:
	sf::Vector2f m_Position;

	std::unique_ptr<sf::RectangleShape> m_Rectangle;
	std::unique_ptr<sf::Sprite> m_Sprite;

	bool m_RotationEnabled = true;
	bool m_PositionEnabled = true;
	bool m_ScaleEnabled = true;

};