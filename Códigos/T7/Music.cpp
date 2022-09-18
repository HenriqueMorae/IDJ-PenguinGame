#include "Music.h"
#include "SDL.h"
#include "Resources.h"

Music::Music() {
	music = nullptr;
}

Music::Music(std::string file) {
	music = nullptr;
	Open(file);
}

void Music::Play(int times) {
	if (Mix_PlayMusic(music.get(), times) == -1) {
		SDL_Log("Unable to play MIX: %s", Mix_GetError());
		std::abort();
	}
}

void Music::Stop(int msToStop) {
	Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
	music = Resources::GetMusic(file);
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
}

void Music::Volume(int volume) {
	Mix_VolumeMusic(volume);
}
