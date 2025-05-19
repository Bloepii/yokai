#include "yokai/world.h"

#include "FastNoise/FastNoise.h"

namespace Yokai
{
    void World::generate(const std::span<std::shared_ptr<WorldGenerator>> &generators) noexcept
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

    std::span<TerrainType> World::get_terrain() noexcept
    {
        return std::span<TerrainType>{terrain};
    }

    std::span<float> World::get_elevation() noexcept
    {
        return std::span<float>(elevation);
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
                const TerrainType t = terrain[y * width + x];
                const float e = elevation[y * width + x];
                out << to_color_kanji(t, e);
            }
            out << '\n';
        }
    }

}
