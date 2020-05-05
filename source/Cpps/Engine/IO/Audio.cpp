#include "Headers/Engine/IO/Audio.h"

void list_audio_devices(const ALCchar *devices) {
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;

    fprintf(stdout, "Devices list:\n");
    fprintf(stdout, "----------\n");
    while (device && *device != '\0' && next && *next != '\0') {
        fprintf(stdout, "%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    fprintf(stdout, "----------\n");
}

ALenum to_al_format(short channels, short samples) {
    bool stereo = (channels > 1);

    switch (samples) {
        case 16:
            if (stereo)
                return AL_FORMAT_STEREO16;
            else
                return AL_FORMAT_MONO16;
        case 8:
            if (stereo)
                return AL_FORMAT_STEREO8;
            else
                return AL_FORMAT_MONO8;
        default:
            return -1;
    }
}



Audio::Audio() {
    //DEVICE CREATION:
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Device Failed to be Created!" << std::endl;
    }

    enumeration = alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE)
        std::cout << "enumeration not supported" << std::endl;
    else
        std::cout << "enumeration supported" << std::endl;

    list_audio_devices(alcGetString(nullptr, ALC_DEVICE_SPECIFIER));

    //CONTEXT CREATION:
    context = alcCreateContext(device, nullptr);
    if (!alcMakeContextCurrent(context)) {
        std::cerr << "Failed to create openal context" << std::endl;
        throw;
    }
}

Audio::~Audio() {
    //CLEAN UP:
    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
