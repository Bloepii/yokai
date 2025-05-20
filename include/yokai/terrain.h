#ifndef YOKAI_TERRAIN_H
#define YOKAI_TERRAIN_H

#include <string>
#include <format>

namespace Yokai
{

    enum class TerrainType : uint8_t
    {
        WATER,
        LAND,
        MOUNTAIN,
        SAND,
        SNOW,
        SHELL,
        WHALE,
        FISH,
        CORAL,
        SEAWEED,
        SHARK,
        TURTLE,
        CRAB,
        OCTOPUS,
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
        case TerrainType::SAND: // yellow
            return Rgb(255, 255, 0);
        case TerrainType::SNOW: // slightly blue
            return Rgb(200, 200, 255);
        case TerrainType::SHELL: // white
            return Rgb(255, 255, 255);
        case TerrainType::WHALE: // gray
            return Rgb(128, 128, 128);
        case TerrainType::FISH: // orange
            return Rgb(255, 165, 0);
        case TerrainType::CORAL: // pink
            return Rgb(255, 192, 203);
        case TerrainType::SEAWEED: // green
            return Rgb(0, 128, 0);
        case TerrainType::SHARK: // dark gray
            return Rgb(105, 105, 105);
        case TerrainType::TURTLE: // green
            return Rgb(0, 128, 0);
        case TerrainType::CRAB: // red
            return Rgb(255, 0, 0);
        case TerrainType::OCTOPUS: // purple
            return Rgb(128, 0, 128);
        default:
            return Rgb(0, 0, 0);
        }
    }

    constexpr std::string_view to_kanji(const TerrainType terrain) noexcept
    {
        switch (terrain)
        {
        case TerrainType::WATER:
            return "水";
        case TerrainType::LAND:
            return "土";
        case TerrainType::MOUNTAIN:
            return "山";
        case TerrainType::SAND:
            return "浜";
        case TerrainType::SNOW:
            return "雪";
        case TerrainType::SHELL:
            return "貝";
        case TerrainType::WHALE:
            return "鯨";
        case TerrainType::FISH:
            return "魚";
        case TerrainType::CORAL:
            return "礁";
        case TerrainType::SEAWEED:
            return "藻";
        case TerrainType::SHARK:
            return "鮫";
        case TerrainType::TURTLE:
            return "亀";
        case TerrainType::CRAB:
            return "蟹";
        case TerrainType::OCTOPUS:
            return "蛸";
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

        return std::format(
            "\033[38:2::{}:{}:{}m{}\033[39m",
            r, g, b,
            to_kanji(terrain)
        );
    }
}

#endif // YOKAI_TERRAIN_H
