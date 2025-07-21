#include <Game/Game.hpp>

int main()
{
    const sf::Vector2u windowSize = {1920, 1080};
    const std::string title = "Super cool flappy game";
    const float framerate = 144;
    float gravity = -9.8f;
    

    Game* game = new Game(windowSize, title, framerate);
    game->Init(gravity);
    game->Run();
    game->Shutdown();
	return 0;
}
