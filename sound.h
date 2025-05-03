#ifndef GAME_SOUND
#define GAME_SOUND

#include <fstream>
#include <vector>
#include <iostream>

bool loadWavFile(const char* filename, ALuint& buffer) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    char header[44];
    file.read(header, 44);

    if (std::string(header, 4) != "RIFF" || std::string(header + 8, 4) != "WAVE") {
        return false;
    }

    int dataSize = *reinterpret_cast<int*>(header + 40);
    std::vector<char> data(dataSize);
    file.read(data.data(), dataSize);

    short channels = *reinterpret_cast<short*>(header + 22);
    int sampleRate = *reinterpret_cast<int*>(header + 24);
    short bitsPerSample = *reinterpret_cast<short*>(header + 34);

    ALenum format = 0;
    if (channels == 1 && bitsPerSample == 8) format = AL_FORMAT_MONO8;
    else if (channels == 1 && bitsPerSample == 16) format = AL_FORMAT_MONO16;
    else if (channels == 2 && bitsPerSample == 8) format = AL_FORMAT_STEREO8;
    else if (channels == 2 && bitsPerSample == 16) format = AL_FORMAT_STEREO16;
    else return false;

    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, data.data(), dataSize, sampleRate);
    return true;
}

#endif