#include "yokai/world.h"

#include "FastNoise/FastNoise.h"

namespace Yokai
{
    void World::generate(const std::span<std::shared_ptr<WorldGenerator>> &generators)
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

    std::span<TerrainType> World::get_terrain()
    {
        return std::span<TerrainType>{terrain};
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
