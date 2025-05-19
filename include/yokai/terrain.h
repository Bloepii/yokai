#ifndef YOKAI_TERRAIN_H
#define YOKAI_TERRAIN_H

#include <string>

namespace Yokai
{

    enum class [[nodiscard]] TerrainType : uint8_t
    {
        WATER,
        LAND,
        MOUNTAIN,
        BEACH,
        SNOW,
    };

    struct Rgb
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        Rgb(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
    };

    constexpr Rgb to_rgb(const TerrainType terrain) noexcept
    {
        switch (terrain)
        {
        case TerrainType::WATER:
            return Rgb(40, 40, 255);
        case TerrainType::LAND:
            return Rgb(100, 190, 20);
        case TerrainType::MOUNTAIN: // brown
            return Rgb(139, 69, 19);
        case TerrainType::BEACH: // yellow
            return Rgb(255, 255, 0);
        case TerrainType::SNOW: // slightly blue
            return Rgb(200, 200, 255);
        default:
            return Rgb(0, 0, 0);
        }
    }

    constexpr std::string to_kanji(const TerrainType terrain) noexcept
    {
        switch (terrain)
        {
        case TerrainType::WATER:
            return "水";
        case TerrainType::LAND:
            return "土";
        case TerrainType::MOUNTAIN:
            return "山";
        case TerrainType::BEACH:
            return "浜";
        case TerrainType::SNOW:
            return "雪";
        default:
            return "?";
        }
    }

    constexpr std::string to_color_kanji(const TerrainType terrain, float brightness) noexcept
    {
        // scale brightness to the range [0.25, 1]
        brightness = (brightness < 0.25f) ? 0.25f : (brightness > 0.75f) ? 1.0f
                                                                         : ((brightness - 0.25f) * 1.5f) + 0.25f;
        const Rgb base_color = to_rgb(terrain);
        const uint8_t r = static_cast<uint8_t>(base_color.r * brightness);
        const uint8_t g = static_cast<uint8_t>(base_color.g * brightness);
        const uint8_t b = static_cast<uint8_t>(base_color.b * brightness);
        const std::string kanji = to_kanji(terrain);
        return "\033[38:2::" + std::to_string(r) + ":" + std::to_string(g) + ":" + std::to_string(b) + "m" + kanji + "\033[39m";
    }
}

#endif // YOKAI_TERRAIN_H
