#pragma once

#include "../Mouse/Mouse.cpp"

class Sound
{
public:
    Sound(string path);
    Sound(string path, bool isMusic);
    void playM();
    int isPlaying();
    int isPaused();
    void pauseM();
    void continueM();
    void stopM();
    void volumeM(int volume);
    void play();
    void play(int channel);
    void play(int channel, int volume);
    void pause();
    void pause(int channel);
    void continue_();
    void continue_(int channel);
    void stop();
    void stop(int channel);
    void volume(int volume);
    void volume(int channel, int volume);
    ~Sound();

private:
    Mix_Music *music = NULL;
    Mix_Chunk *soundReflex = NULL;
};