#include <string>
#include "SDL_mixer.h"

#ifndef MUSIC_H
#define MUSIC_H

// Classe "Music" que cuida de abrir e tocar musicas
class Music {
	private:
		Mix_Music* music;

	public:
		Music();
		Music(std::string file);
		~Music();
		void Play(int times = -1);
		void Stop(int msToStop = 1500);
		void Open(std::string file);
		bool IsOpen();
		void Volume(int volume);
};

#endif // MUSIC_H
