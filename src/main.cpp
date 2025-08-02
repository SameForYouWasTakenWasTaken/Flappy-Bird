#include <Game/Game.hpp>

int main()
{
    constexpr sf::Vector2u windowSize = {1920, 1080};
    constexpr char title[] = "Super cool flappy game";
    constexpr float framerate = 144;
    constexpr float gravity = -9.8f;


    auto* game = new Game(windowSize, title, framerate);
    game->Init(gravity);
    game->Run();
    game->Shutdown();
	return 0;
}
