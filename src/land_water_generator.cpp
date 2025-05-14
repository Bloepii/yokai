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

#include "../include/yokai/land_water_generator.h"

#include "../include/yokai/terrain.h"

namespace Yokai
{

    LandWaterGenerator::LandWaterGenerator(float freq, uint8_t octaves, float lacunarity) : frequency{freq}
    {
        fnFractal->SetSource(fnSimplex);
        fnFractal->SetOctaveCount(octaves);
        fnFractal->SetLacunarity(lacunarity);
    }

    void LandWaterGenerator::generate(const std::shared_ptr<World> &world) const noexcept
    {
        const uint8_t w = world->get_width();
        const uint8_t h = world->get_height();
        const auto map = world->get_map();

        std::vector<float> noiseOutput(w * h);
        fnFractal->GenUniformGrid2D(noiseOutput.data(), 0, 0, w, h, frequency, world->get_seed());
        for (std::size_t y = 0; y < h; ++y)
        {
            for (std::size_t x = 0; x < w; ++x)
            {
                map[y * w + x] = (noiseOutput[y * w + x] < -0.5f) ? TerrainType::WATER : TerrainType::LAND;
            }
        }
    }
}
