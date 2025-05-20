#include "yokai/random_point_generator.h"

namespace Yokai
{
    void RandomPointGenerator::generate(World& world) const
    {
        const auto w = world.get_width();
        const auto h = world.get_height();
        // if frequency is 0.01, then 1% of the points will be generated
        const auto num_points = static_cast<std::size_t>(w * h * frequency);
        // distribution for a random point
        std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<std::size_t> random_point(0, w * h - 1);

        for (std::size_t i = 0; i < num_points; ++i)
        {
            // Generate a random point
            const auto random_index = random_point(generator);
            // Check if the terrain type is in the allowed locations
            if (std::find(locations.begin(), locations.end(), world.get_terrain()[random_index]) != locations.end())
            {
                // If it is, set the terrain type to the point type
                world.get_terrain()[random_index] = point;
            }
        }
    }
}
