#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

namespace Console 
{
    enum Color {
        RESET = 0,
        DEFAULT = RESET,
        GREEN = 1,
        BLUE = 2,
        YELLOW = 3,
        RED = 4,
        RED_BG = 5,
        BLACK = 6
    };

    enum Level {
        TRACE = 0,
        INFO = 1,
        DEBUG = 2,
        WARNING = 3,
        ERROR = 4,
        FATAL = 5
    };

    #define COLOR_RESET  "\033[0m"
    #define COLOR_GREEN  "\033[0;32m"
    #define COLOR_BLUE   "\033[0;34m"
    #define COLOR_YELLOW "\033[0;33m"
    #define COLOR_RED    "\033[0;31m"
    #define COLOR_RED_BG "\033[0;41m"
    #define COLOR_BLACK  "\033[0;30m"

    static const char* GetColorCode(Color color) {
        switch (color) {
            case Color::GREEN:   return COLOR_GREEN;
            case Color::BLUE:    return COLOR_BLUE;
            case Color::YELLOW:  return COLOR_YELLOW;
            case Color::RED:     return COLOR_RED;
            case Color::RED_BG:  return COLOR_RED_BG;
            case Color::BLACK:   return COLOR_BLACK;
            default:            return COLOR_RESET;
        }
    }

    static Color GetLevelColor(Level level) {
        switch (level) {
            case Level::TRACE:   return Color::DEFAULT;
            case Level::INFO:    return Color::GREEN;
            case Level::DEBUG:   return Color::BLUE;
            case Level::WARNING: return Color::YELLOW;
            case Level::ERROR:   return Color::RED;
            case Level::FATAL:   return Color::RED_BG;
            default:            return Color::DEFAULT;
        }
    }

    template<typename... Args>
    static void Log(Args&&... args) {
        Log(Level::TRACE, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void DLog(Args&&... args) {
        Log(Level::DEBUG, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void ILog(Args&&... args) {
        Log(Level::INFO, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void WLog(Args&&... args) {
        Log(Level::WARNING, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void ELog(Args&&... args) {
        Log(Level::ERROR, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void FLog(Args&&... args) {
        Log(Level::FATAL, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void Log(Level level, Args&&... args) {
        static const char* level_strs[] = {
            "[TRACE]: ",
            "[INFO]:  ",
            "[DEBUG]: ",
            "[WARN]:  ",
            "[ERROR]: ",
            "[FATAL]: "
        };

        std::ostringstream oss;
        oss << GetColorCode(GetLevelColor(level)) << level_strs[static_cast<int>(level)];
        (oss << ... << std::forward<Args>(args));
        oss << COLOR_RESET << '\n';

        std::cout << oss.str();
    }

    template<typename... Args>
    static void Println(Color color, Args&&... args) {
        std::ostringstream oss;
        oss << GetColorCode(color);
        (oss << ... << std::forward<Args>(args));
        oss << COLOR_RESET << '\n';

        std::cout << oss.str();
    }

    template<typename... Args>
    static void Println(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        oss << '\n';

        std::cout << oss.str();
    }
}