#include <array>
#include <memory>
#include <cstddef>
#include <cstdint>
#include <span>
#include <iostream>
#include <fstream>
#include <random>
#include <limits>
#include <chrono>
#include <concepts>

#include "yokai/world.h"
#include "yokai/world_generator.h"
#include "yokai/land_water_generator.h"
#include "yokai/config.h"
#include "yokai/random_point_generator.h"

using namespace Yokai;

template <std::derived_from<WorldGenerator> T, typename... Args>
std::unique_ptr<WorldGenerator> make_generator(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

int main(const int argc, const char *argv[])
{
    Config c{argc, argv};

    std::array generators {
        // Continents
        make_generator<LandWaterGenerator>(c.frequency, c.octaves, c.gain, c.lacunarity, c.waterlevel),

        // Animals
        make_generator<RandomPointGenerator>(TerrainType::SAND, 0.05, TerrainType::SHELL),
        make_generator<RandomPointGenerator>(TerrainType::SAND, 0.05, TerrainType::CRAB),

        make_generator<RandomPointGenerator>(TerrainType::WATER, 0.001, TerrainType::WHALE),
        make_generator<RandomPointGenerator>(TerrainType::WATER, 0.01, TerrainType::FISH),
        make_generator<RandomPointGenerator>(TerrainType::WATER, 0.02, TerrainType::CORAL),
        make_generator<RandomPointGenerator>(TerrainType::WATER, 0.02, TerrainType::SEAWEED),
        make_generator<RandomPointGenerator>(TerrainType::WATER, 0.001, TerrainType::SHARK),
        make_generator<RandomPointGenerator>(TerrainType::WATER, 0.01, TerrainType::TURTLE),
        make_generator<RandomPointGenerator>(TerrainType::WATER,  0.01, TerrainType::OCTOPUS),
    };


    World world { c.width, c.height, c.seed };
    world.generate(generators);

    {
        std::ofstream file("world.txt", std::ios::trunc);
        if (file)
            world.display(file, c.truecolor);
    }

    world.display(std::cout, c.truecolor);
}
