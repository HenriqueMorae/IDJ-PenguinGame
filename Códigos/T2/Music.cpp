#include "Music.h"
#include "SDL.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file) {
	music = nullptr;
	Open(file);
}

void Music::Play(int times) {
	if (Mix_PlayMusic(music, times) == -1) {
		SDL_Log("Unable to play MIX: %s", Mix_GetError());
		std::abort();
	}
}

void Music::Stop(int msToStop) {
	Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
	music = Mix_LoadMUS(file.c_str());
	if (music == nullptr) {
		SDL_Log("Unable to open MIX: %s", Mix_GetError());
		std::abort();
	}
}

bool Music::IsOpen() {
	if (music != nullptr) {
		return true;
	} else {
		return false;
	}
}

Music::~Music() {
	Stop();
	Mix_FreeMusic(music);
}

void Music::Volume(int volume) {
	Mix_VolumeMusic(volume);
}
