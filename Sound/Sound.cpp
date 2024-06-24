#include "Sound.h"

Sound::Sound(string path)
{
    const char *file = path.c_str();
    this->soundReflex = Mix_LoadWAV(file);
    if (this->soundReflex == NULL)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}
void Sound::play()
{
    Mix_PlayChannel(-1, this->soundReflex, 0);
}

Sound::~Sound()
{
    if (this->music)
    {
        Mix_FreeMusic(this->music);
        this->music = nullptr;
    }
    else
    {
        Mix_FreeChunk(this->soundReflex);
        this->soundReflex = nullptr;
    }
};
