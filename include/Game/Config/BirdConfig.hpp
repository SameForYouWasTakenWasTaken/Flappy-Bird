#include <SFML/Graphics.hpp>

namespace BirdConfig {
	// When the bird falls/goes up, it will tilt by a specific amount.
	const sf::Angle MaximumAngle = sf::degrees(80.0f); // Up tilt
	const sf::Angle MinimumAngle = sf::degrees(-80.0f); // Down tilt

	const sf::Keyboard::Key FlapKey = sf::Keyboard::Key::Space;

	const int dim_BirdTextureX = 200;
	const int dim_BirdTextureY = 200;

	const float UpwardForce = 4.5f;
}