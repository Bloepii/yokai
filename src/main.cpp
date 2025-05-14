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
#include "../include/yokai/world_generator.h"
#include "../include/yokai/land_water_generator.h"

using namespace Yokai;
int main(const int argc, const char *argv[]) noexcept
{
    int width = 20;                                                                  // Default width
    int height = 10;                                                                 // Default height
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count(); // Default seed

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-w" && i + 1 < argc)
        {
            width = std::stoi(argv[++i]);
        }
        else if (arg == "-h" && i + 1 < argc)
        {
            height = std::stoi(argv[++i]);
        }
        else if (arg == "-s" && i + 1 < argc)
        {
            seed = static_cast<unsigned int>(std::stoul(argv[++i]));
        }
        else
        {
            std::cerr << "Unknown or incomplete argument: " << arg << std::endl;
            return 1;
        }
    }

    std::vector<std::unique_ptr<const WorldGenerator>> generators{};
    generators.emplace_back(std::make_unique<const LandWaterGenerator>());
    const auto world = std::make_shared<World>(width, height, seed);
    world->generate(generators);

    {
        std::ofstream file("world.txt", std::ios::trunc);
        if (file)
            world->display(file);
    }

    world->display(std::cout);
}
