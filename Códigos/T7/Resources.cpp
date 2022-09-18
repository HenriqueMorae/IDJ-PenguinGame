#include "Resources.h"
#include "Game.h"
#include "SDL_image.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::const_iterator tex = imageTable.find(file);

	if (tex == imageTable.end()) {
		Game& jogo = Game::GetInstance();
		SDL_Renderer* renderizador = jogo.GetRenderer();
		SDL_Texture* texture = IMG_LoadTexture(renderizador, file.c_str());

		if (texture == nullptr) {
			SDL_Log("Unable to initialize IMG: %s", SDL_GetError());
			std::abort();
		}

		std::shared_ptr<SDL_Texture> texturePtr(texture, [](SDL_Texture* texturah) { delete texturah; });
		std::pair<std::string, std::shared_ptr<SDL_Texture>> novopar(file,texturePtr);
		imageTable.insert(novopar);
		return texturePtr;
	} else {
		return tex->second;
	}
}

void Resources::ClearImages() {
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator itr;

	for (itr = imageTable.begin(); itr != imageTable.end(); itr++) {
		if (itr->second.unique()) {
			SDL_DestroyTexture(itr->second.get());
			imageTable.erase(itr);
		}
	}
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
	std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::const_iterator mus = musicTable.find(file);

	if (mus == musicTable.end()) {
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		if (music == nullptr) {
			SDL_Log("Unable to open MIX: %s", Mix_GetError());
			std::abort();
		}

		std::shared_ptr<Mix_Music> musicPtr(music, [](Mix_Music* musicah) { delete musicah; });
		std::pair<std::string, std::shared_ptr<Mix_Music>> novopar(file,musicPtr);
		musicTable.insert(novopar);
		return musicPtr;
	} else {
		return mus->second;
	}
}

void Resources::ClearMusics() {
	std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator itr;

	for (itr = musicTable.begin(); itr != musicTable.end(); itr++) {
		if (itr->second.unique()) {
			Mix_FreeMusic(itr->second.get());
			musicTable.erase(itr);
		}
	}
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
	std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::const_iterator snd = soundTable.find(file);

	if (snd == soundTable.end()) {
		Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
		if (chunk == nullptr) {
			SDL_Log("Unable to open MIX: %s", Mix_GetError());
			std::abort();
		}

		std::shared_ptr<Mix_Chunk> chunkPtr(chunk, [](Mix_Chunk* chunki) { delete chunki; });
		std::pair<std::string, std::shared_ptr<Mix_Chunk>> novopar(file,chunkPtr);
		soundTable.insert(novopar);
		return chunkPtr;
	} else {
		return snd->second;
	}
}

void Resources::ClearSounds() {
	std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator itr;

	for (itr = soundTable.begin(); itr != soundTable.end(); itr++) {
		if (itr->second.unique()) {
			Mix_FreeChunk(itr->second.get());
			soundTable.erase(itr);
		}
	}
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int ptsize) {
	std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::const_iterator ttf = fontTable.find(file + std::to_string(ptsize));

	if (ttf == fontTable.end()) {
		TTF_Font* font = TTF_OpenFont(file.c_str(), ptsize);
		if (font == nullptr) {
			SDL_Log("Unable to open TTF: %s", file.c_str());
			std::abort();
		}

		std::shared_ptr<TTF_Font> fontPtr(font, [](TTF_Font* fonti) { delete fonti; });
		std::pair<std::string, std::shared_ptr<TTF_Font>> novopar(file + std::to_string(ptsize),fontPtr);
		fontTable.insert(novopar);
		return fontPtr;
	} else {
		return ttf->second;
	}
}

void Resources::ClearFonts() {
	std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::iterator itr;

	for (itr = fontTable.begin(); itr != fontTable.end(); itr++) {
		if (itr->second.unique()) {
			TTF_CloseFont(itr->second.get());
			fontTable.erase(itr);
		}
	}
}
