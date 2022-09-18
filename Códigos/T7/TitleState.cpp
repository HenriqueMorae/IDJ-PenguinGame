#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "SDL.h"
#include "Game.h"
#include "StageState.h"
#include "CameraFollower.h"
#include "Text.h"
#include "Camera.h"

TitleState::TitleState() {
	Camera::pos.x = 0;
	Camera::pos.y = 0;

	GameObject* bg = new GameObject();
	Sprite* sprite = new Sprite(*bg, "img/title.jpg");
	bg->AddComponent(sprite);
	CameraFollower* cf = new CameraFollower(*bg);
	bg->AddComponent(cf);
	objectArray.emplace_back(bg);

	tt = new GameObject();
	Text* text = new Text(*tt, "font/CallMeMaybe.ttf", 24, Text::SOLID, "Pressione ESPACO para jogar", {255, 0, 0, 255});
	tt->AddComponent(text);
	tt->box.x = 512 - tt->box.w/2;
	tt->box.y = 500;
	objectArray.emplace_back(tt);
	off = false;
}

TitleState::~TitleState() {

}

void TitleState::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		Game& jogo = Game::GetInstance();
		jogo.Push(new StageState());
	}

	UpdateArray(dt);
	timerText.Update(dt);

	if (timerText.Get() > 0.5) {
		timerText.Restart();
		off = !off;

		if (off) {
			tt->box.y = 1000;
		} else {
			tt->box.y = 500;
		}
	}
}

void TitleState::LoadAssets() {

}

void TitleState::Start() {
	StartArray();
}

void TitleState::Render() {
	RenderArray();
}

void TitleState::Pause() {

}

void TitleState::Resume() {
	Camera::pos.x = 0;
	Camera::pos.y = 0;
}
