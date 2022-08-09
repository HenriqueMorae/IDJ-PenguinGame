#include <unordered_map>
#include <string>
#include "SDL.h"
#include "SDL_mixer.h"

#ifndef RESOURCES_H
#define RESOURCES_H

// Classe "Resources" que gerencia as texturas
class Resources {
	private:
		static std::unordered_map<std::string, SDL_Texture*> imageTable;
		static std::unordered_map<std::string, Mix_Music*> musicTable;
		static std::unordered_map<std::string, Mix_Chunk*> soundTable;

	public:
		static SDL_Texture* GetImage(std::string file);
		static void ClearImages();
		static Mix_Music* GetMusic(std::string file);
		static void ClearMusics();
		static Mix_Chunk* GetSound(std::string file);
		static void ClearSounds();
};

#endif // RESOURCES_H
