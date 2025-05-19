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
        const unsigned int seed;

        static unsigned int generate_random_seed()
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<unsigned int> dist(0, std::numeric_limits<unsigned int>::max());
            return dist(mt);
        }

    public:
        World(const std::size_t w, const std::size_t h, const unsigned int s = generate_random_seed())
            : width{w}, height{h}, terrain(w * h, TerrainType::WATER), elevation(w * h, 0), seed{s} {}

        [[nodiscard]] unsigned int get_seed() const noexcept;

        [[nodiscard]] std::span<TerrainType> get_terrain() noexcept;

        [[nodiscard]] std::span<float> get_elevation() noexcept;

        [[nodiscard]] std::size_t get_width() const noexcept;

        [[nodiscard]] std::size_t get_height() const noexcept;

        void generate(const std::span<std::shared_ptr<WorldGenerator>> &generators) noexcept;

        void display(std::ostream &out, bool truecolor) const;
    };

}

#endif // YOKAI_WORLD_H
