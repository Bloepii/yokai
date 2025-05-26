#include "yokai/random_point_generator.h"

namespace Yokai
{
    void RandomPointGenerator::generate(World &world) const
    {
        // if frequency is 0.01, then 1% of the points will be generated
        const auto num_points = static_cast<std::size_t>(world.get_terrain().size() * frequency);
        // distribution for a random point
        auto generator = world.get_generator();

        auto random_point = world.world_distribution();

        for (std::size_t i = 0; i < num_points; ++i)
        {
            // Generate a random point
            const auto random_index = random_point(*generator);
            // Check if the terrain type is in the allowed locations
            if (std::find(locations.begin(), locations.end(), world.get_tile(random_index)) != locations.end())
            {
                // If it is, set the terrain type to the point type
                world.set_tile(random_index, point);
            }
        }
    }
}
