#include <vector>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <span>
#include <iostream>
#include <fstream>
#include <random>
#include <limits>
#include <chrono>

#include "../include/yokai/world.h"

#include "../include/FastNoise/FastNoise.h"

namespace Yokai
{
    void World::generate(const std::vector<std::unique_ptr<const WorldGenerator>> &generators) noexcept
    {
        for (const auto &gen : generators)
        {
            gen->generate(shared_from_this());
        }
    }

    unsigned int World::get_seed() const noexcept
    {
        return seed;
    }

    std::span<TerrainType> World::get_map() noexcept
    {
        return std::span<TerrainType>{map};
    }

    std::size_t World::get_width() const noexcept
    {
        return width;
    }

    std::size_t World::get_height() const noexcept
    {
        return height;
    }

    void World::display(std::ostream &out) const
    {
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                const TerrainType val = map[y * width + x];
                out << (val == TerrainType::LAND ? 'L' : 'W');
            }
            out << '\n';
        }
    }

}
