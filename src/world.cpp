#include "yokai/world.h"

#include "FastNoise/FastNoise.h"

namespace Yokai
{
    void World::generate(std::span<std::unique_ptr<WorldGenerator>> generators)
    {
        for (const auto &gen : generators)
        {
            gen->generate(*this);
        }
    }

    uint32_t World::get_seed() const
    {
        return seed;
    }

    std::shared_ptr<std::mt19937> World::get_generator()
    {
        return generator;
    }

    std::span<TerrainType> World::get_terrain()
    {
        return std::span<TerrainType>{terrain};
    }

    TerrainType World::get_tile(std::size_t idx) const
    {
        return terrain[idx];
    }

    void World::set_tile(std::size_t idx, TerrainType type)
    {
        terrain[idx] = type;
    }

    std::span<float> World::get_elevation()
    {
        return std::span<float>(elevation);
    }

    std::size_t World::get_width() const
    {
        return width;
    }

    std::size_t World::get_height() const
    {
        return height;
    }

    std::uniform_int_distribution<std::size_t> &World::world_distribution()
    {
        return distribution;
    }

    void World::display(std::ostream &out, bool truecolor) const
    {
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                const TerrainType t = terrain[y * width + x];
                const float e = truecolor ? 1 : elevation[y * width + x];
                out << to_color_kanji(t, e);
            }
            out << '\n';
        }
    }

}
