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

#include "yokai/world.h"
#include "yokai/world_generator.h"
#include "yokai/land_water_generator.h"
#include "yokai/config.h"
#include "yokai/random_point_generator.h"

using namespace Yokai;
int main(const int argc, const char *argv[])
{
    Config c{argc, argv};
    // Use pointers to base class for polymorphism
    auto generators = std::vector<std::shared_ptr<WorldGenerator>>{};

    const auto continents = std::make_shared<LandWaterGenerator>(c.frequency, c.octaves, c.gain, c.lacunarity, c.waterlevel);
    const auto shells = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::SAND}, 0.05, TerrainType::SHELL);
    const auto whales = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::WATER}, 0.001, TerrainType::WHALE);
    const auto fish = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::WATER}, 0.01, TerrainType::FISH);
    const auto coral = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::WATER}, 0.02, TerrainType::CORAL);
    const auto seaweed = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::WATER}, 0.02, TerrainType::SEAWEED);
    const auto sharks = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::WATER}, 0.001, TerrainType::SHARK);
    const auto turtles = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::WATER}, 0.01, TerrainType::TURTLE);
    const auto crabs = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::SAND}, 0.05, TerrainType::CRAB);
    const auto octopuses = std::make_shared<RandomPointGenerator>(std::vector<TerrainType>{TerrainType::WATER}, 0.01, TerrainType::OCTOPUS);

    generators.emplace_back(continents);

    // animals
    generators.emplace_back(shells);
    generators.emplace_back(whales);
    generators.emplace_back(fish);
    generators.emplace_back(coral);
    generators.emplace_back(seaweed);
    generators.emplace_back(sharks);
    generators.emplace_back(turtles);
    generators.emplace_back(crabs);
    generators.emplace_back(octopuses);

    World world { c.width, c.height, c.seed };
    world.generate(std::span<std::shared_ptr<WorldGenerator>>{generators});

    {
        std::ofstream file("world.txt", std::ios::trunc);
        if (file)
            world.display(file, c.truecolor);
    }

    world.display(std::cout, c.truecolor);
}
