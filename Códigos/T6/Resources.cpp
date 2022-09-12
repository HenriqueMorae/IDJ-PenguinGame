#include "Resources.h"
#include "Game.h"
#include "SDL_image.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
	std::unordered_map<std::string, SDL_Texture*>::const_iterator tex = imageTable.find(file);

	if (tex == imageTable.end()) {
		Game& jogo = Game::GetInstance();
		SDL_Renderer* renderizador = jogo.GetRenderer();
		SDL_Texture* texture = IMG_LoadTexture(renderizador, file.c_str());

		if (texture == nullptr) {
			SDL_Log("Unable to initialize IMG: %s", SDL_GetError());
			std::abort();
		}

		std::pair<std::string, SDL_Texture*> novopar(file,texture);
		imageTable.insert(novopar);
		return texture;
	} else {
		return tex->second;
	}
}

void Resources::ClearImages() {
	std::unordered_map<std::string, SDL_Texture*>::iterator itr;

	for (itr = imageTable.begin(); itr != imageTable.end(); itr++) {
		SDL_DestroyTexture(itr->second);
	}
	imageTable.clear();
}


Mix_Music* Resources::GetMusic(std::string file) {
	std::unordered_map<std::string, Mix_Music*>::const_iterator mus = musicTable.find(file);

	if (mus == musicTable.end()) {
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		if (music == nullptr) {
			SDL_Log("Unable to open MIX: %s", Mix_GetError());
			std::abort();
		}

		std::pair<std::string, Mix_Music*> novopar(file,music);
		musicTable.insert(novopar);
		return music;
	} else {
		return mus->second;
	}
}

void Resources::ClearMusics() {
	std::unordered_map<std::string, Mix_Music*>::iterator itr;

	for (itr = musicTable.begin(); itr != musicTable.end(); itr++) {
		Mix_FreeMusic(itr->second);
	}
	musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file) {
	std::unordered_map<std::string, Mix_Chunk*>::const_iterator snd = soundTable.find(file);

	if (snd == soundTable.end()) {
		Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
		if (chunk == nullptr) {
			SDL_Log("Unable to open MIX: %s", Mix_GetError());
			std::abort();
		}

		std::pair<std::string, Mix_Chunk*> novopar(file,chunk);
		soundTable.insert(novopar);
		return chunk;
	} else {
		return snd->second;
	}
}

void Resources::ClearSounds() {
	std::unordered_map<std::string, Mix_Chunk*>::iterator itr;

	for (itr = soundTable.begin(); itr != soundTable.end(); itr++) {
		Mix_FreeChunk(itr->second);
	}
	soundTable.clear();
}
