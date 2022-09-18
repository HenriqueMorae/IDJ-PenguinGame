#include "EndState.h"
#include "GameData.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Text.h"
#include "InputManager.h"
#include "Game.h"
#include "TitleState.h"
#include "Sprite.h"

EndState::EndState() {
	Camera::pos.x = 0;
	Camera::pos.y = 0;

	if (GameData::playerVictory) {
		GameObject* bg = new GameObject();
		Sprite* sprite = new Sprite(*bg, "img/win.jpg");
		bg->AddComponent(sprite);
		CameraFollower* cf = new CameraFollower(*bg);
		bg->AddComponent(cf);
		objectArray.emplace_back(bg);

		backgroundMusic = new Music("audio/endStateWin.ogg");
	} else {
		GameObject* bg = new GameObject();
		Sprite* sprite = new Sprite(*bg, "img/lose.jpg");
		bg->AddComponent(sprite);
		CameraFollower* cf = new CameraFollower(*bg);
		bg->AddComponent(cf);
		objectArray.emplace_back(bg);

		backgroundMusic = new Music("audio/endStateLose.ogg");
	}

	GameObject* tt = new GameObject();
	Text* text = new Text(*tt, "font/CallMeMaybe.ttf", 24, Text::SOLID, "Pressione ESC para sair ou ESPACO para jogar de novo", {255, 0, 0, 255});
	tt->AddComponent(text);
	tt->box.x = 512 - tt->box.w/2;
	tt->box.y = 550;
	objectArray.emplace_back(tt);
}

EndState::~EndState() {
	backgroundMusic->Stop(0);
}

void EndState::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		popRequested = true;
		Game& jogo = Game::GetInstance();
		jogo.Push(new TitleState());
	}

	UpdateArray(dt);
}

void EndState::LoadAssets() {

}

void EndState::Start() {
	backgroundMusic->Volume(32);
	backgroundMusic->Play();
	StartArray();
}

void EndState::Render() {
	RenderArray();
}

void EndState::Pause() {

}

void EndState::Resume() {
	Camera::pos.x = 0;
	Camera::pos.y = 0;
}
