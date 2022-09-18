#include <memory>
#include "Component.h"
#include "SDL.h"
#include "SDL_ttf.h"

#ifndef TEXT_H
#define TEXT_H

// Classe "Text"
// COMPONENT
class Text : public Component {
	public:
		enum TextStyle {SOLID, SHADED, BLENDED};
		Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
		~Text();
		void Render();
		void Update(float dt);
		bool Is(std::string type);
		void SetText(std::string text);
		void SetColor(SDL_Color color);
		void SetStyle(TextStyle style);
		void SetFontFile(std::string fontFile);
		void SetFontSize(int fontSize);

	private:
		std::shared_ptr<TTF_Font> font;
		SDL_Texture* texture;
		std::string text;
		TextStyle style;
		std::string fontFile;
		int fontSize;
		SDL_Color color;

		void RemakeTexture();
};

#endif // TEXT_H
