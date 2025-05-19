#include "yokai/land_water_generator.h"

#include "yokai/terrain.h"

namespace Yokai
{

    LandWaterGenerator::LandWaterGenerator(const float freq, const uint8_t octaves, const float gain, const float lacunarity, const float cutoff) : frequency{freq}, cutoff{cutoff}
    {
        fnFractal->SetSource(fnSimplex);
        fnFractal->SetOctaveCount(octaves);
        fnFractal->SetLacunarity(lacunarity);
        fnFractal->SetGain(gain);
    }

    void LandWaterGenerator::generate(const std::shared_ptr<World> &world) const noexcept
    {
        const uint8_t w = world->get_width();
        const uint8_t h = world->get_height();
        const auto terrain = world->get_terrain();
        const auto elevation = world->get_elevation();

        std::vector<float> noiseOutput(w * h);
        fnFractal->GenUniformGrid2D(noiseOutput.data(), 0, 0, w, h, frequency, world->get_seed());
        for (std::size_t y = 0; y < h; ++y)
        {
            for (std::size_t x = 0; x < w; ++x)
            {
                const float value = noiseOutput[y * w + x];

                if (value < cutoff)
                {
                    terrain[y * w + x] = TerrainType::WATER;
                }
                else if (value < cutoff + 0.1f) // Beach threshold
                {
                    terrain[y * w + x] = TerrainType::BEACH;
                }
                else if (value < cutoff + 0.4f) // Land threshold
                {
                    terrain[y * w + x] = TerrainType::LAND;
                }
                else if (value < cutoff + 0.6f) // Mountain threshold
                {
                    terrain[y * w + x] = TerrainType::MOUNTAIN;
                }
                else // Snow mountain threshold
                {
                    terrain[y * w + x] = TerrainType::SNOW;
                }

                // Scale elevation to 0-1 (from -0.5 to 0.5)
                elevation[y * w + x] = (value + 0.5f) / 1.0f;
            }
        }
    }
}
