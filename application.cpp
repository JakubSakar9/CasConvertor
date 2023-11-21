#include <iostream>
#include "formats/wav.h"
#include "auxiliary/log.h"

int main() {
    Wav input;
    input.load("../data/test.wav");
    Logger::logLevel = LOG_LEVEL_ERROR;
//    LFATAL("Fatal error");
//    LERROR("Error");
//    LWARN("Warning");
//    LINFO("Info");
//    LDEBUG("Debug");
    Logger::log(LOG_LEVEL_FATAL, "Fatal error\n");
    Logger::log(LOG_LEVEL_ERROR, "Error\n");
    Logger::log(LOG_LEVEL_WARN, "Warning\n");
    Logger::log(LOG_LEVEL_INFO, "Info\n");
    Logger::log(LOG_LEVEL_DEBUG, "Debug\n");

    return 0;
}
