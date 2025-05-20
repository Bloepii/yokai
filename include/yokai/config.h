#ifndef YOKAI_CONFIG_H
#define YOKAI_CONFIG_H

#include <random>

namespace Yokai
{

    struct Config
    {
        std::size_t width = 80;                 // Default width
        std::size_t height = 50;                // Default height
        uint32_t seed = std::random_device{}(); // Default seed
        float frequency = 0.01;                 // Default frequency
        float gain = 0.75;                      // Default gain
        float lacunarity = 2.0;                 // Default lacunarity
        int octaves = 8;                        // Default octaves
        float waterlevel = -0.05;               // Default water level
        bool truecolor = false;                 // Default true color

        Config(int argc, const char *argv[]);
    };

}

#endif // YOKAI_CONFIG_H
