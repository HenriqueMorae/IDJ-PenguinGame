#include "State.h"
#include "Face.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

#define PI 3.14159265359

State::State() {
	quitRequested = false;

	GameObject* bg = new GameObject();
	Sprite* sprite = new Sprite(*bg, "img/ocean.jpg");
	bg->AddComponent(sprite);
	CameraFollower* cf = new CameraFollower(*bg);
	bg->AddComponent(cf);
	bg->box.x = 0;
	bg->box.y = 0;
	objectArray.emplace_back(bg);

	// Instanciar um um Music
	music = new Music("audio/stageState.ogg");
	music->Volume(32);
	music->Play();

	GameObject* tm = new GameObject();
	TileSet* ts = new TileSet(64, 64, "img/tileset.png");
	TileMap* tilemap = new TileMap(*tm, "map/tileMap.txt", ts);
	tm->AddComponent(tilemap);
	tm->box.x = 0;
	tm->box.y = 0;
	objectArray.emplace_back(tm);
}

State::~State() {
	objectArray.clear();
}

// Carregar assets
void State::LoadAssets() {

}

void State::Update (float dt) {
	Camera::Update(dt);

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		Vec2 objPos = Vec2(200, 0).Rotate(-PI + PI*(rand() % 1001)/500.0) + Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
		AddObject((int)objPos.x, (int)objPos.y);
	}

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin()+i);
		}
	}
}

void State::Render() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->GetComponent("TileMap") != nullptr) {
			objectArray[i]->box.x = Camera::pos.x;
			objectArray[i]->box.y = Camera::pos.y;
		}

		objectArray[i]->Render();
	}
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::AddObject(int mouseX, int mouseY) {
	GameObject* pinguim = new GameObject();
	Sprite* sprite = new Sprite(*pinguim, "img/penguinface.png");
	pinguim->AddComponent(sprite);
	pinguim->box.x = mouseX - sprite->GetWidth()/2 - Camera::pos.x;
	pinguim->box.y = mouseY - sprite->GetHeight()/2 - Camera::pos.y;
	Sound* som = new Sound(*pinguim, "audio/boom.wav");
	som->Volume(64);
	pinguim->AddComponent(som);
	Face* face = new Face(*pinguim);
	pinguim->AddComponent(face);
	objectArray.emplace_back(pinguim);
}
