#include "Headers/Engine/Audio/Sound.h"

Sound::Sound(const char *filename) noexcept {
    ALuint source{}, buffer{};

    //SOURCE:
    alGenSources((ALuint)1, &source);

    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);

    //BUFFER:
    alGenBuffers((ALuint)1, &buffer);

    //LOAD AUDIO TO BUFFER:
    WaveInfo *wave = WaveOpenFileForReading(filename); //@todo figure out if this pointer needs to be deleted
    if (!wave) {
        fprintf(stderr, "failed to read wave file\n");
        return;
    }

    int ret = WaveSeekFile(0, wave); //I don't think this needs to be freed or deallocated
    if (ret) {
        fprintf(stderr, "failed to seek wave file\n");
        return;
    }

    auto bufferData = std::make_unique<char[]>(wave->dataSize); //buffer will automatically be cleaned up
    if (!bufferData) {
        perror("malloc");
        return;
    }

    ret = WaveReadFile(bufferData.get(), wave->dataSize, wave);
    if (ret != wave->dataSize) {
        fprintf(stderr, "short read: %d, want: %d\n", ret, wave->dataSize);
        return;
    }

    //LOAD RAW AUDIO STREAM:
    alBufferData(buffer, to_al_format(wave->channels, wave->bitsPerSample),
                 bufferData.get(), wave->dataSize, wave->sampleRate);

    soundBufferContainer = std::make_shared<SoundResourceContainer>(source, buffer);
}

void Sound::bind() const noexcept {
    //BIND SOURCE TO BUFFER:
    alSourcei(soundBufferContainer->getSource(), AL_BUFFER, soundBufferContainer->getBuffer());
}

void Sound::play() const noexcept {
    bind();

    //PLAY AUDIO:
    alSourcePlay(soundBufferContainer->getSource());

    ALint source_state;
    alGetSourcei(soundBufferContainer->getSource(), AL_SOURCE_STATE, &source_state);
    while (source_state == AL_PLAYING) {
        alGetSourcei(soundBufferContainer->getSource(), AL_SOURCE_STATE, &source_state);
    }
}
