#ifndef YOKAI_WORLD_GENERATOR_H
#define YOKAI_WORLD_GENERATOR_H

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

#include "world.h"

namespace Yokai
{
    class World;

    struct [[nodiscard]] WorldGenerator
    {
        virtual void generate(const std::shared_ptr<World> &world) const noexcept = 0;
        virtual ~WorldGenerator() = default;
    };

}

#endif // YOKAI_WORLD_GENERATOR_H