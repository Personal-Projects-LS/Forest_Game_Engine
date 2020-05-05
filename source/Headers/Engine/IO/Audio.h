#pragma once

#include <iostream>
#include <cstring>

#include <audio/wave.h>
#include <AL/al.h>
#include <AL/alc.h>

void list_audio_devices(const ALCchar *devices);
ALenum to_al_format(short channels, short samples);

class Audio {
public:
    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    Audio();

    ~Audio();

private:
    ALCdevice *device;
    ALboolean enumeration;
    ALCcontext *context;
};
