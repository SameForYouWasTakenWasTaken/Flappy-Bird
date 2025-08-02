#include <SFML/Graphics.hpp>

namespace PipeConfig {
	constexpr int PipeLifeTime = 7; // The lifetime of the pipe in seconds


	constexpr float PipeSpeed = 600.0f; // -x direction

	constexpr float top_PipeSpawnOffset = -900.0f; // The offset between the top pipe and the bottom pipe


	constexpr float bottom_XPipeSpawnOffset = 550.0f; // Additional offset to the right

	constexpr float bottom_MaximumPipeSpawnHeight = 360.0f; // Maximum height
	constexpr float bottom_MinimumPipeSpawnHeight = 950.0f; // Minimum height
}