#ifndef YOKAI_TERRAIN_H
#define YOKAI_TERRAIN_H

#include <cstdint>

namespace Yokai
{

    enum class [[nodiscard]] TerrainType : uint8_t
    {
        WATER,
        LAND,
    };

}

#endif // YOKAI_TERRAIN_H
