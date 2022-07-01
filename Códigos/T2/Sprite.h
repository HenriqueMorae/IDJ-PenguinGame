#include <string>
#include "SDL.h"
#include "Component.h"
#include "GameObject.h"

#ifndef SPRITE_H
#define SPRITE_H

// Classe "Sprite" que cuida de carregar e renderizar imagens
// COMPONENT
class Sprite : public Component {
	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;

	public:
		Sprite(GameObject& associated);
		Sprite(GameObject& associated, std::string file);
		~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void Render();
		int GetWidth();
		int GetHeight();
		bool IsOpen();
		void Update(float dt);
		bool Is(std::string type);
};

#endif // SPRITE_H
