//
// Created by Jetsy on 11/21/2023.
//

#ifndef CASCONVERTOR_WAV_H
#define CASCONVERTOR_WAV_H

#include <fstream>
#include "../defines.h"

struct Wav {
    u32 numBytes;
    u32 sampleRate;
    u32 byteRate;
    u32 numSamples;
    u16 bitsPerSample;
    u16 blockAlign;
    u16 numChannels = CHANNEL_COUNT_INVALID;
    char *data = nullptr;

    /// Constructor
    Wav() = default;

    /// Destructor
    ~Wav() {
        delete[] data;
    }

    /// Loads a WAV file from the given path
    bool load(const char *path);
};


#endif //CASCONVERTOR_WAV_H
