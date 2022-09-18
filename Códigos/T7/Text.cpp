#include "Text.h"
#include "Resources.h"
#include "Game.h"
#include "Camera.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated) {
	texture = nullptr;
	this->text = text;
	this->style = style;
	this->fontFile = fontFile;
	this->fontSize = fontSize;
	this->color = color;
	font = Resources::GetFont(fontFile, fontSize);

	RemakeTexture();
}

Text::~Text() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void Text::Update(float dt) {

}

void Text::Render() {
	if (texture != nullptr) {
		Game& jogo = Game::GetInstance();
		SDL_Renderer* renderizador = jogo.GetRenderer();

		SDL_Rect clipRect;
		clipRect.x = 0;
		clipRect.y = 0;
		clipRect.w = associated.box.w;
		clipRect.h = associated.box.h;

		SDL_Rect dstRect;
		dstRect.x = associated.box.x + Camera::pos.x;
		dstRect.y = associated.box.y + Camera::pos.y;
		dstRect.w = associated.box.w;
		dstRect.h = associated.box.h;

		if (SDL_RenderCopyEx(renderizador, texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0) {
			SDL_Log("Unable to initialize TEXT: %s", SDL_GetError());
			std::abort();
		}
	}
}

bool Text::Is(std::string type) {
	if (type == "Text" || type == "text") {
		return true;
	} else {
		return false;
	}
}

void Text::SetText(std::string text) {
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
	this->fontFile = fontFile;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::RemakeTexture() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}

	font = Resources::GetFont(fontFile, fontSize);
	SDL_Surface* sf = nullptr;

	switch (style) {
		case SOLID:
			sf = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		case SHADED:
			sf = TTF_RenderText_Shaded(font.get(), text.c_str(), color, {0, 0, 0, 255});
			break;
		case BLENDED:
			sf = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;
		default:
			break;
	}

	if (sf == nullptr) {
		SDL_Log("Unable to initialize Texture");
		std::abort();
	}

	Game& jogo = Game::GetInstance();
	SDL_Renderer* renderizador = jogo.GetRenderer();

	texture = SDL_CreateTextureFromSurface(renderizador, sf);
	if (texture == nullptr) {
		SDL_Log("Unable to initialize Texture: %s", SDL_GetError());
		std::abort();
	}

	associated.box.h = sf->h;
	associated.box.w = sf->w;

	SDL_FreeSurface(sf);
}
