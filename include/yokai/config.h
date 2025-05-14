#ifndef YOKAI_CONFIG_H
#define YOKAI_CONFIG_H

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

namespace Yokai
{

    struct Config
    {
        int width = 80;                                                                  // Default width
        int height = 50;                                                                 // Default height
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count(); // Default seed
        double frequency = 0.01;                                                         // Default frequency
        double gain = 0.75;                                                              // Default gain
        double lacunarity = 2.0;                                                         // Default lacunarity
        int octaves = 8;                                                                 // Default octaves
        double waterlevel = -0.05;                                                       // Default water level

        Config(int argc, const char *argv[]);
    };

}

#endif // YOKAI_CONFIG_H