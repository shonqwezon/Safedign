#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace config {
    constexpr bool OPEN = true;
    constexpr bool CLOSED = false;
    constexpr unsigned short port {7890};
    constexpr int open{ 1 };
    constexpr int close{ 0 };
    const std::string host{ "192.168.1.61" };
    const std::string start{ "200" };
    const std::string shutdown{ "400" };
}

#endif