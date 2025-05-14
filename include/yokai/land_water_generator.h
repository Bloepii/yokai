#ifndef YOKAI_LAND_WATER_GENERATOR_H
#define YOKAI_LAND_WATER_GENERATOR_H

#include <memory>

#include "../FastNoise/FastNoise.h"
#include "world_generator.h"

namespace Yokai
{
    class [[nodiscard]] LandWaterGenerator final : public WorldGenerator
    {
    private:
        const FastNoise::SmartNode<FastNoise::Simplex> fnSimplex = FastNoise::New<FastNoise::Simplex>();
        const FastNoise::SmartNode<FastNoise::FractalFBm> fnFractal = FastNoise::New<FastNoise::FractalFBm>();
        const float frequency;

    public:
        LandWaterGenerator(float freq = 0.1f, uint8_t octaves = 4, float lacunarity = 2.0f);

        void generate(const std::shared_ptr<World> &world) const noexcept override;
    };
}

#endif // YOKAI_LAND_WATER_GENERATOR_H