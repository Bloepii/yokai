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

    void LandWaterGenerator::generate(World& world) const
    {
        const auto terrain = world.get_terrain();
        const auto elevation = world.get_elevation();

        std::vector<float> noiseOutput(terrain.size());
        fnFractal->GenUniformGrid2D(
            noiseOutput.data(),
            0, 0, world.get_width(), world.get_height(),
            frequency,
            world.get_seed()
        );

        auto noise_it = noiseOutput.begin();
        auto terrain_it = terrain.begin();
        auto elevation_it = elevation.begin();
        for (; noise_it != noiseOutput.end(); ++noise_it, ++terrain_it, ++elevation_it) {

            const float value = *noise_it;

            if (value < cutoff)
            {
                *terrain_it = TerrainType::WATER;
            }
            else if (value < cutoff + 0.1f) // Beach threshold
            {
                *terrain_it = TerrainType::SAND;
            }
            else if (value < cutoff + 0.4f) // Land threshold
            {
                *terrain_it = TerrainType::LAND;
            }
            else if (value < cutoff + 0.6f) // Mountain threshold
            {
                *terrain_it = TerrainType::MOUNTAIN;
            }
            else // Snow mountain threshold
            {
                *terrain_it = TerrainType::SNOW;
            }

            *elevation_it = (value + 0.5f) / 1.0f;
        }
    }
}
