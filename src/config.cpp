#include <iostream>

#include <sys/ioctl.h>
#include <unistd.h>

#include "yokai/config.h"

namespace Yokai
{

    Config::Config(int argc, const char *argv[])
    {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        width = (w.ws_col / 2);
        height = w.ws_row;

        for (int i = 1; i < argc; ++i)
        {
            auto parseArgument = [&](const std::string &arg, const std::string &flag, auto &value, auto converter)
            {
                if (arg == flag && i + 1 < argc)
                {
                    value = converter(argv[++i]);
                    return true;
                }
                return false;
            };

            std::string arg = argv[i];
            if (arg == "--help")
            {
                std::cout << "Usage: program [options]\n"
                          << "Options:\n"
                          << "  -w <width>       Set the width (integer)\n"
                          << "  -h <height>      Set the height (integer)\n"
                          << "  -s <seed>        Set the seed (unsigned integer)\n"
                          << "  -f <frequency>   Set the frequency (double)\n"
                          << "  -g <gain>        Set the gain (double)\n"
                          << "  -l <lacunarity>  Set the lacunarity (double)\n"
                          << "  -o <octaves>     Set the octaves (integer)\n"
                          << "  -a <waterlevel>  Set the water level (double)\n"
                          << "  -t <truecolor>   Set true color (boolean)\n"
                          << "  --help           Display this help message\n";
                std::exit(0);
            }
            else if (parseArgument(arg, "-w", width, [](const char *val)
                                   { return std::stoull(val); }) ||
                     parseArgument(arg, "-h", height, [](const char *val)
                                   { return std::stoull(val); }) ||
                     parseArgument(arg, "-s", seed, [](const char *val)
                                   { return static_cast<unsigned int>(std::stoul(val)); }) ||
                     parseArgument(arg, "-f", frequency, [](const char *val)
                                   { return std::stof(val); }) ||
                     parseArgument(arg, "-g", gain, [](const char *val)
                                   { return std::stof(val); }) ||
                     parseArgument(arg, "-l", lacunarity, [](const char *val)
                                   { return std::stof(val); }) ||
                     parseArgument(arg, "-o", octaves, [](const char *val)
                                   { return std::stoi(val); }) ||
                     parseArgument(arg, "-a", waterlevel, [](const char *val)
                                   { return std::stof(val); }) ||
                     (arg == "-t" ? (truecolor = true, true) : false))
            {
                continue;
            }
            else
            {
                std::cerr << "Unknown or incomplete argument: " << arg << std::endl;
                throw std::invalid_argument("Invalid argument");
            }
        }
    }
}
