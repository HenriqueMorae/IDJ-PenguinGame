#include "Sprite.h"
#include "Game.h"
#include "SDL_image.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	height = 0;
	width = 0;
	this->associated.box.h = 0;
	this->associated.box.w = 0;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated) {
	texture = nullptr;
	Open(file);
}

Sprite::~Sprite() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void Sprite::Open(std::string file) {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	Game& jogo = Game::GetInstance();
	SDL_Renderer* renderizador = jogo.GetRenderer();
	texture = IMG_LoadTexture(renderizador, file.c_str());

	if (texture == nullptr) {
		SDL_Log("Unable to initialize IMG: %s", SDL_GetError());
		std::abort();
	}

	if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
		SDL_Log("Unable to initialize IMG: %s", SDL_GetError());
		std::abort();
	}

	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
	this->associated.box.h = h;
	this->associated.box.w = w;
}

void Sprite::Render() {
	Game& jogo = Game::GetInstance();
	SDL_Renderer* renderizador = jogo.GetRenderer();

	SDL_Rect dstRect;
	dstRect.x = associated.box.x;
	dstRect.y = associated.box.y;
	dstRect.w = associated.box.w;
	dstRect.h = associated.box.h;

	if (SDL_RenderCopy(renderizador, texture, &clipRect, &dstRect) != 0) {
		SDL_Log("Unable to initialize IMG: %s", SDL_GetError());
		std::abort();
	}
}

int Sprite::GetWidth() {
	return width;
}

int Sprite::GetHeight() {
	return height;
}

bool Sprite::IsOpen() {
	if (texture != nullptr) {
		return true;
	} else {
		return false;
	}
}

void Sprite::Update(float dt) {

}

bool Sprite::Is(std::string type) {
	if (type == "Sprite" || type == "sprite") {
		return true;
	} else {
		return false;
	}
}
