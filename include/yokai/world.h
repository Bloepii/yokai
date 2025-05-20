#ifndef YOKAI_WORLD_H
#define YOKAI_WORLD_H

#include <vector>
#include <span>
#include <ostream>
#include <random>
#include <limits>

#include "terrain.h"
#include "world_generator.h"

namespace Yokai
{
    class WorldGenerator;

    class [[nodiscard]] World final : public std::enable_shared_from_this<World>
    {
    private:
        const std::size_t width;
        const std::size_t height;
        std::vector<TerrainType> terrain;
        std::vector<float> elevation;
        const uint32_t seed;

    public:
        World(std::size_t w, std::size_t h, const uint32_t s = std::random_device{}())
            : width{w}, height{h}, terrain(w * h, TerrainType::WATER), elevation(w * h, 0), seed{s} {}

        [[nodiscard]] unsigned int get_seed() const;

        [[nodiscard]] std::span<TerrainType> get_terrain();
        [[nodiscard]] TerrainType get_tile(std::size_t idx) const;
        void set_tile(std::size_t idx, TerrainType type);

        [[nodiscard]] std::span<float> get_elevation();

        [[nodiscard]] std::size_t get_width() const;

        [[nodiscard]] std::size_t get_height() const;

        [[nodiscard]] std::uniform_int_distribution<std::size_t> world_distribution() const;

        void generate(std::span<std::unique_ptr<WorldGenerator>> generators);

        void display(std::ostream &out, bool truecolor) const;
    };

}

#endif // YOKAI_WORLD_H
