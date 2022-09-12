#include <string>
#include "SDL.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

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
		Vec2 scale;
		SDL_RendererFlip flip;
		int frameCount;
		int currentFrame;
		float timeElapsed;
		float frameTime;
		Timer selfDestructCount;
		float secondsToSelfDestruct;

	public:
		Sprite(GameObject& associated);
		Sprite(GameObject& associated, std::string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
		~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void Render(int x, int y);
		void Render();
		int GetWidth();
		int GetHeight();
		bool IsOpen();
		void Update(float dt);
		bool Is(std::string type);
		void SetScale(float scaleX, float scaleY);
		void SetFlip(SDL_RendererFlip fl);
		Vec2 GetScale();
		void SetFrame(int frame);
		void SetFrameCount(int frameCount);
		void SetFrameTime(float frameTime);
};

#endif // SPRITE_H
