#ifndef YOKAI_WORLD_GENERATOR_H
#define YOKAI_WORLD_GENERATOR_H

#include <memory>

#include "yokai/world.h"

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