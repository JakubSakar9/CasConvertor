//
// Created by Jetsy on 11/21/2023.
//

#include <cwchar>
#include "../defines.h"

#ifndef CASCONVERTOR_LOG_H
#define CASCONVERTOR_LOG_H

inline constexpr u32 LOG_LEVEL_FATAL = 0;
inline constexpr u32 LOG_LEVEL_ERROR = 1;
inline constexpr u32 LOG_LEVEL_WARN = 2;
inline constexpr u32 LOG_LEVEL_INFO = 3;
inline constexpr u32 LOG_LEVEL_DEBUG = 4;

#ifdef _WIN32
#include <windows.h>
#include <wincon.h>
#include <iostream>

#define LFATAL(format, ...) Logger::log(LOG_LEVEL_FATAL, format, __VA_ARGS__)
#define LERROR(format, ...) Logger::log(LOG_LEVEL_ERROR, format, __VA_ARGS__)
#define LWARN(format, ...) Logger::log(LOG_LEVEL_WARN, format, __VA_ARGS__)
#define LINFO(format, ...) Logger::log(LOG_LEVEL_INFO, format, __VA_ARGS__)
#define LDEBUG(format, ...) Logger::log(LOG_LEVEL_DEBUG, format, __VA_ARGS__)

u8 chars[5] = {FOREGROUND_RED | FOREGROUND_INTENSITY,
               FOREGROUND_RED,
               FOREGROUND_RED | FOREGROUND_GREEN,
               FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
               FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE};
#endif

namespace Logger {
    u32 logLevel;
    void log(u32 level, const char *format, ...) {
        if (level <= logLevel) {
#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, chars[level]);
            std::cout << "[";
            switch (level) {
                case LOG_LEVEL_FATAL:
                    std::cout << "FATAL";
                    break;
                case LOG_LEVEL_ERROR:
                    std::cout << "ERROR";
                    break;
                case LOG_LEVEL_WARN:
                    std::cout << "WARN";
                    break;
                case LOG_LEVEL_INFO:
                    std::cout << "INFO";
                    break;
                case LOG_LEVEL_DEBUG:
                    std::cout << "DEBUG";
                    break;
            }
            std::cout << "] ";
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif
        }
    }
}

#endif //CASCONVERTOR_LOG_H
