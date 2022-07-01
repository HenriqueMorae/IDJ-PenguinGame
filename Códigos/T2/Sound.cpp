#include "Sound.h"
#include "SDL.h"

Sound::Sound(GameObject& associated) : Component(associated) {
	chunk = nullptr;
	channel = -1;
}

Sound::Sound(GameObject& associated, std::string file) : Component(associated) {
	chunk = nullptr;
	channel = -1;
	Open(file);
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, chunk, times-1);
	if (channel == -1) {
		SDL_Log("Unable to play MIX: %s", Mix_GetError());
		std::abort();
	}
}

void Sound::Stop() {
	if (chunk != nullptr) {
		 Mix_HaltChannel(channel);
	}
}

void Sound::Open(std::string file) {
	chunk = Mix_LoadWAV(file.c_str());
	if (chunk == nullptr) {
		SDL_Log("Unable to open MIX: %s", Mix_GetError());
		std::abort();
	}
}

bool Sound::IsPlaying() {
	if (channel == -1) {
		return false;
	} else {
		int tocando = Mix_Playing(channel);
		if (tocando == 0) {
			return false;
		} else {
			return true;
		}
	}
}

Sound::~Sound() {
	if (chunk != nullptr) {
		Mix_HaltChannel(channel);
		Mix_FreeChunk(chunk);
	}
}

bool Sound::IsOpen() {
	if (chunk != nullptr) {
		return true;
	} else {
		return false;
	}
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(std::string type) {
	if (type == "Sound" || type == "sound") {
		return true;
	} else {
		return false;
	}
}

void Sound::Volume(int volume) {
	Mix_VolumeChunk(chunk, volume);
}
