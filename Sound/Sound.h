#pragma once

#include "../Mouse/Mouse.cpp"

class Sound
{
public:
    Sound(string path);
    void play();
    ~Sound();

private:
    Mix_Music *music = NULL;
    Mix_Chunk *soundReflex = NULL;
};