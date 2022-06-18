#include <string>
#include "SDL.h"

#ifndef SPRITE_H
#define SPRITE_H

// Classe "Sprite" que cuida de carregar e renderizar imagens
class Sprite {
	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;

	public:
		Sprite();
		Sprite(std::string file);
		~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void Render(int x, int y);
		int GetWidth();
		int GetHeight();
		bool IsOpen();
};

#endif // SPRITE_H
