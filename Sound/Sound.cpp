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

Sound::Sound(string path, bool isMusic)
{
    const char *file = path.c_str();
    this->music = Mix_LoadMUS(file);
	if (this->music == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void Sound::playM()
{
    Mix_PlayMusic(this->music, -1);
}

int Sound::isPlaying()
{
   return Mix_PlayingMusic();
}

int Sound::isPaused()
{
    return Mix_PausedMusic();
}

void Sound::pauseM()
{
    Mix_PauseMusic();
}

void Sound::continueM()
{
    Mix_ResumeMusic();
}

void Sound::stopM()
{
    Mix_HaltMusic();
}

void Sound::volumeM(int volume)
{
    Mix_VolumeMusic(volume);
}

void Sound::play()
{
    Mix_PlayChannel(-1, this->soundReflex, 0);
}

void Sound::play(int channel)
{
    Mix_PlayChannel(channel, this->soundReflex, 0);
}

void Sound::play(int channel, int volume)
{
    Mix_PlayChannel(channel, this->soundReflex, 0);
    Mix_Volume(channel, volume);
}

void Sound::pause()
{
    Mix_Pause(-1);
}

void Sound::pause(int channel)
{
    Mix_Pause(channel);
}

void Sound::continue_()
{
    Mix_Resume(-1);
}

void Sound::continue_(int channel)
{
    Mix_Resume(channel);
}

void Sound::stop()
{
    Mix_HaltChannel(-1);
}

void Sound::stop(int channel)
{
    Mix_HaltChannel(channel);
}

void Sound::volume(int volume)
{
    Mix_Volume(-1, volume);
}

void Sound::volume(int channel, int volume)
{
    Mix_Volume(channel, volume);
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
