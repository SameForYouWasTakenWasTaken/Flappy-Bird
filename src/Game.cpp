#include <iostream>
#include <filesystem>
#include <string>
#include <memory>
#include <vector>

#include "Game/Game.hpp"
#include "Game/Pipe.hpp"
#include "Game/Config/BirdConfig.hpp"
#include "Game/Config/PipeConfig.hpp"

namespace fs = std::filesystem;

Game::Game(const sf::Vector2u windowSize, const std::string& title, unsigned int framerate)
{
	m_Window.create(sf::VideoMode(windowSize), title);
	m_Window.setFramerateLimit(framerate);
}

void Game::Init(float gravity) {
	
	// Make sure the images in './assets/images/' are valid and can be assigned to a texture
	sf::Texture* temp_texture = new sf::Texture();

	for (const auto& entry : fs::recursive_directory_iterator("assets/images")) {
		if(temp_texture->loadFromFile(entry.path())) { 
			std::cout << "Loaded image: " << entry.path() << '\n';
		}
		else {
			std::cerr << "Failed to load image: " << entry.path() << '\n';
		}
	}

	// Create the bird
	m_Bird = std::make_unique<Bird>(gravity);


	// Clean memory
	delete temp_texture;
}


void Game::ProcessEvents() {
	bool pressed_jump_button = false;

	while (const std::optional event = m_Window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			Shutdown();

		// Flaps the bird if the keybind is pressed
		m_Bird->Flap();
	}
}

void Game::Render() {
	m_Window.clear();

	// Draw the bird
	m_Bird->Draw(m_Window);

	// Draw the spawned pipes
	for (const auto& pipe_group : m_Pipes) {
		pipe_group.bottomPipe->Draw(m_Window);
		pipe_group.topPipe->Draw(m_Window);
	}

	m_Window.display();
}

void Game::Update(float dt) {
	// Pipe spawner
	if (m_PipeSpawnClock.getElapsedTime().asSeconds() >= PipeConfig::PipeLifeTime) {
		// true means the pipe is rotated 180 degrees
		std::unique_ptr<Pipe> bottom_pipe = std::make_unique<Pipe>(m_Window); // Creates the bottom pipe with a random height
		std::unique_ptr<Pipe> top_pipe = std::make_unique<Pipe>(m_Window, bottom_pipe); // Offsets the top pipe compared to the bottom pipe
		
		PipeGroup group;
		group.topPipe = std::move(top_pipe);
		group.bottomPipe = std::move(bottom_pipe);

		m_Pipes.push_back(std::move(group));
		m_PipeSpawnClock.restart();
	}

	// Update the bird
	m_Bird->Update(dt);

	// Update current pipes
	for (const auto& pipe_group : m_Pipes) {
		pipe_group.bottomPipe->Update(dt);
		pipe_group.topPipe->Update(dt);
	}

	// Check for any possible collisions
	for (const auto& pipe_group : m_Pipes) {
		pipe_group.bottomPipe->checkCollision(m_Bird);
		pipe_group.topPipe->checkCollision(m_Bird);
	}

	//  Remove expired pipes
	m_Pipes.erase(
		std::remove_if(m_Pipes.begin(), m_Pipes.end(), [](const PipeGroup& pipe_group) {
			return pipe_group.bottomPipe->isExpired || pipe_group.topPipe->isExpired;
			}),
		m_Pipes.end()
	);
	 
}

void Game::Run() {
	sf::Clock dt_clock;

	m_PipeSpawnClock.start();
	while (m_Window.isOpen())
	{
		// Grab the delta time
		float dt = dt_clock.restart().asSeconds(); 

		ProcessEvents();
		Update(dt);
		Render();
	}
}

void Game::Shutdown() {
	m_Window.close();
}