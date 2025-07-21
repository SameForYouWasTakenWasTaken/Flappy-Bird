#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>

#include "Game/Bird.hpp"
#include "Game/Pipe.hpp"

class Game {
public:
	// Construct functions
	Game(const sf::Vector2u windowSize, const std::string& title, unsigned int framerate);
	void Init(float gravity);
	void Run();
	void Shutdown();

	// Rendering functions
	void ProcessEvents();
	void Render();
	void Update(float dt);

private:
	sf::RenderWindow m_Window;
	sf::Clock m_PipeSpawnClock;
	std::vector<PipeGroup> m_Pipes;

	std::unique_ptr<Bird> m_Bird;
};