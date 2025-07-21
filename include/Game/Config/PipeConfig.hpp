#include <SFML/Graphics.hpp>

namespace PipeConfig {
	const int PipeLifeTime = 7; // The lifetime of the pipe in seconds


	const float PipeSpeed = 600.0f; // -x direction 

	const float top_PipeSpawnOffset = -900.0f; // The offset between the top pipe and the bottom pipe


	const float bottom_XPipeSpawnOffset = 550.0f; // Additional offset to the right

	const float bottom_MaximumPipeSpawnHeight = 360.0f; // Maximum height
	const float bottom_MinimumPipeSpawnHeight = 950.0f; // Minimum height
}