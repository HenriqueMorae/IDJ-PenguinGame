#include "State.h"

State::State() {
	quitRequested = false;

	// Instanciar um Sprite e um Music
	bg = new Sprite("img/ocean.jpg");
	music = new Music("audio/stageState.ogg");
	music->Play();
}

// Carregar assets
void State::LoadAssets() {

}

void State::Update (float dt) {
	if (SDL_QuitRequested()) quitRequested = true;
}

void State::Render() {
	// Render do fundo
	bg->Render(0, 0);
}

bool State::QuitRequested() {
	return quitRequested;
}
