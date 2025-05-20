#ifndef YOKAI_WORLD_GENERATOR_H
#define YOKAI_WORLD_GENERATOR_H

#include <memory>

#include "yokai/world.h"

namespace Yokai
{
    class World;

    struct [[nodiscard]] WorldGenerator
    {
        virtual void generate(World& world) const = 0;
        virtual ~WorldGenerator() = default;
    };

}

#endif // YOKAI_WORLD_GENERATOR_H
