#ifndef YOKAI_LAND_WATER_GENERATOR_H
#define YOKAI_LAND_WATER_GENERATOR_H

#include <memory>

#include "FastNoise/FastNoise.h"
#include "yokai/world_generator.h"

namespace Yokai
{
    class [[nodiscard]] LandWaterGenerator final : public WorldGenerator
    {
    private:
        const FastNoise::SmartNode<FastNoise::Simplex> fnSimplex = FastNoise::New<FastNoise::Simplex>();
        const FastNoise::SmartNode<FastNoise::FractalFBm> fnFractal = FastNoise::New<FastNoise::FractalFBm>();
        const float frequency;
        const float cutoff;

    public:
        LandWaterGenerator(const float freq = 0.01f, const uint8_t octaves = 4, const float gain = 0.5f, const float lacunarity = 2.0f, const float cutoff = -0.1f);

        void generate(World& world) const override;
    };
}

#endif // YOKAI_LAND_WATER_GENERATOR_H
