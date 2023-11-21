//
// Created by Jetsy on 11/21/2023.
//

#include <cstring>
#include "wav.h"

bool Wav::load(const char *path) {
    std::fstream s{path, std::ios::in | std::ios::binary};
    if (!s.is_open()) {
        std::fprintf(stderr, "Failed to open file: %s\n", path);
        return false;
    }

    // Check RIFF header
    char check[5] = {0, 0, 0, 0, 0};
    s.read(check, 4);
    if (std::strncmp(check, "RIFF", 4) != 0) {
        std::fprintf(stderr, "File is not a WAV file: %s\n", path);
        return false;
    }

    // Total chunk size
    u32 chunkSize;
    s.read(reinterpret_cast<char *>(&chunkSize), 4);

    // Check WAVE header
    s.read(check, 4);
    if (std::strncmp(check, "WAVE", 4) != 0) {
        std::fprintf(stderr, "File is not a WAV file: %s\n", path);
        return false;
    }

    // Check fmt header
    s.read(check, 4);
    if (std::strncmp(check, "fmt ", 4) != 0) {
        std::fprintf(stderr, "Could not find fmt header in file: %s\n", path);
        return false;
    }

    // Check fmt chunk size
    u32 fmtChunkSize;
    s.read(reinterpret_cast<char *>(&fmtChunkSize), 4);
    if (fmtChunkSize != 16) {
        std::fprintf(stderr, "fmt chunk is not in the standard format for file: %s\n", path);
        return false;
    }

    // Check audio format
    u16 audioFormat;
    s.read(reinterpret_cast<char *>(&audioFormat), 2);
    if (audioFormat != 1) {
        std::printf("ERROR: Unsupported format (PCM is required): %s\n"
                             "the current format is %d\n", path, audioFormat);
    }

    // Read number of channels
    u16 nc;
    s.read(reinterpret_cast<char *>(&nc), 2);
    if (nc == 1) {
        numChannels = CHANNEL_COUNT_MONO;
    } else if (nc == 2) {
        numChannels = CHANNEL_COUNT_STEREO;
    } else {
        std::fprintf(stderr, "Unsupported number of channels: %d\n", nc);
        return false;
    }

    // Read sample rate
    s.read(reinterpret_cast<char *>(&sampleRate), 4);

    // Read byte rate
    s.read(reinterpret_cast<char *>(&byteRate), 4);

    // Read block align
    s.read(reinterpret_cast<char *>(&blockAlign), 2);

    // Read bits per sample
    s.read(reinterpret_cast<char *>(&bitsPerSample), 2);

    // Check data header
    s.read(check, 4);
    if (std::strncmp(check, "data", 4) != 0 && std::strncmp(check, "fact", 4) != 0) {
        std::fprintf(stderr, "Could not find data header in file: %s\n", path);
        return false;
    }

    // Read data chunk size
    s.read(reinterpret_cast<char *>(&numBytes), 4);
    numSamples = numBytes * 8 / bitsPerSample;
    if (numChannels == CHANNEL_COUNT_STEREO) {
        numSamples >>= 1;
    }

    // Read data
    data = new char[numBytes];
    s.read(data, numBytes);
    return true;
}
