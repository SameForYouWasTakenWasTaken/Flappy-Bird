#include <SFML/Graphics.hpp>

namespace BirdConfig {
	// When the bird falls/goes up, it will tilt by a specific amount.
	constexpr sf::Angle MaximumAngle = sf::degrees(80.0f); // Up tilt
	constexpr sf::Angle MinimumAngle = sf::degrees(-80.0f); // Down tilt

	constexpr auto FlapKey = sf::Keyboard::Key::Space; // The actual flap key

	constexpr int dim_BirdTextureX = 200; // Bird collision box dimension in X
	constexpr int dim_BirdTextureY = 200; // Bird collision box dimension in Y

	constexpr float UpwardForce = 4.5f; // Upward force when you flap
}