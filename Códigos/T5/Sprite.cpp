#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
	texture = nullptr;
	height = 0;
	width = 0;
	this->associated.box.h = 0;
	this->associated.box.w = 0;
	scale.x = 1;
	scale.y = 1;
	flip = SDL_FLIP_NONE;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated) {
	texture = nullptr;
	Open(file);
	scale.x = 1;
	scale.y = 1;
	flip = SDL_FLIP_NONE;
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
	texture = Resources::GetImage(file);

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

void Sprite::Render(int x, int y) {
	Game& jogo = Game::GetInstance();
	SDL_Renderer* renderizador = jogo.GetRenderer();

	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = associated.box.w*scale.x;
	dstRect.h = associated.box.h*scale.y;

	if (SDL_RenderCopyEx(renderizador, texture, &clipRect, &dstRect, associated.angleDeg, nullptr, flip) != 0) {
		SDL_Log("Unable to initialize IMG: %s", SDL_GetError());
		std::abort();
	}
}

void Sprite::Render() {
	Render(associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y);
}

int Sprite::GetWidth() {
	return width*scale.x;
}

int Sprite::GetHeight() {
	return height*scale.y;
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

void Sprite::SetScale(float scaleX, float scaleY) {
	if (scaleX != 0) scale.x = scaleX;
	if (scaleY != 0) scale.y = scaleY;

	float wAntigo = associated.box.w;
	float hAntigo = associated.box.h;
	associated.box.w *= scale.x;
	associated.box.h *= scale.y;
	associated.box.x += (wAntigo-associated.box.w)/2;
	associated.box.y += (hAntigo-associated.box.h)/2;
}

Vec2 Sprite::GetScale() {
	return scale;
}


void Sprite::SetFlip(SDL_RendererFlip fl) {
	flip = fl;
}
