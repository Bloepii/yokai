#ifndef YOKAI_RANDOM_POINT_GENERATOR_H
#define YOKAI_RANDOM_POINT_GENERATOR_H

#include <vector>
#include <random>

#include "yokai/terrain.h"
#include "yokai/world_generator.h"

namespace Yokai
{
    /**
     * RandomPointGenerator is a generic class that takes allowed locations (terrain types)
     * and generates random points of a terrain type on those locations with a certain frequency.
     *
     * - locations: std::span<TerrainType> - The allowed terrain types for point generation.
     * - frequency: double - The frequency of point generation.
     * - point: TerrainType - The terrain type of the generated point.
     */
    class [[nodiscard]] RandomPointGenerator final : public WorldGenerator
    {
    private:
        const std::vector<TerrainType> locations;
        const double frequency;
        const TerrainType point;

    public:
        RandomPointGenerator(std::vector<TerrainType> locs, double freq, TerrainType pt)
            : locations(locs), frequency(freq), point(pt) {}
        void generate(const std::shared_ptr<World> &world) const noexcept override;
    };
}

#endif // YOKAI_RANDOM_POINT_GENERATOR_H