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

using namespace Yokai;
int main(const int argc, const char *argv[]) noexcept
{
    Config c{argc, argv};
    std::array<std::shared_ptr<WorldGenerator>, 1> generators{
        std::make_shared<LandWaterGenerator>(c.frequency, c.octaves, c.gain, c.lacunarity, c.waterlevel)};
    const auto world = std::make_shared<World>(c.width, c.height, c.seed);
    world->generate(generators);

    {
        std::ofstream file("world.txt", std::ios::trunc);
        if (file)
            world->display(file);
    }

    world->display(std::cout);
}
