#include "Sprite.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "Collider.h"
#include "StageState.h"
#include "GameData.h"
#include "Game.h"
#include "EndState.h"

#define PI 3.14159265359

StageState::StageState() {
	quitRequested = false;
	started = false;

	// Instanciar um um Music
	backgroundMusic = new Music("audio/stageState.ogg");

	tileSet = new TileSet(64, 64, "img/tileset.png");
}

StageState::~StageState() {
	backgroundMusic->Stop(0);
	objectArray.clear();
}

void StageState::Start() {
	backgroundMusic->Volume(32);
	backgroundMusic->Play();

	LoadAssets();
	StartArray();
}

// Carregar assets
void StageState::LoadAssets() {
	GameObject* bg = new GameObject();
	Sprite* sprite = new Sprite(*bg, "img/ocean.jpg");
	bg->AddComponent(sprite);
	CameraFollower* cf = new CameraFollower(*bg);
	bg->AddComponent(cf);
	objectArray.emplace_back(bg);

	GameObject* tm = new GameObject();
	TileMap* tilemap = new TileMap(*tm, "map/tileMap.txt", tileSet);
	tm->AddComponent(tilemap);
	tm->box.x = 0;
	tm->box.y = 0;
	objectArray.emplace_back(tm);

	GameObject* alien = new GameObject();
	Alien* al = new Alien(*alien, 3, 0);
	alien->AddComponent(al);
	Sprite* sp = (Sprite*) alien->GetComponent("Sprite");
	alien->box.x = 352 - sp->GetWidth()/2;
	alien->box.y = 320 - sp->GetHeight()/2;
	objectArray.emplace_back(alien);

	GameObject* alien2 = new GameObject();
	Alien* al2 = new Alien(*alien2, 3, 1);
	alien2->AddComponent(al2);
	Sprite* sp2 = (Sprite*) alien2->GetComponent("Sprite");
	alien2->box.x = 1056 - sp2->GetWidth()/2;
	alien2->box.y = 320 - sp2->GetHeight()/2;
	objectArray.emplace_back(alien2);

	GameObject* alien3 = new GameObject();
	Alien* al3 = new Alien(*alien3, 3, 2);
	alien3->AddComponent(al3);
	Sprite* sp3 = (Sprite*) alien3->GetComponent("Sprite");
	alien3->box.x = 352 - sp3->GetWidth()/2;
	alien3->box.y = 960 - sp3->GetHeight()/2;
	objectArray.emplace_back(alien3);

	GameObject* alien4 = new GameObject();
	Alien* al4 = new Alien(*alien4, 3, 3);
	alien4->AddComponent(al4);
	Sprite* sp4 = (Sprite*) alien4->GetComponent("Sprite");
	alien4->box.x = 1056 - sp4->GetWidth()/2;
	alien4->box.y = 960 - sp4->GetHeight()/2;
	objectArray.emplace_back(alien4);

	GameObject* pinguim = new GameObject();
	PenguinBody* pb = new PenguinBody(*pinguim);
	pinguim->AddComponent(pb);
	Sprite* sp5 = (Sprite*) pinguim->GetComponent("Sprite");
	pinguim->box.x = 704 - sp5->GetWidth()/2;
	pinguim->box.y = 640 - sp5->GetHeight()/2;
	objectArray.emplace_back(pinguim);
	Camera::Follow(pinguim);
}

void StageState::Update (float dt) {
	Camera::Update(dt);

	if (InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		popRequested = true;
	}

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);

		if (objectArray[i]->GetComponent("Collider") != nullptr) {
			colliderArray.push_back(objectArray[i]);
		}
	}

	for (unsigned int i = 0; i < colliderArray.size()-1; i++) {
		for (unsigned int j = i+1; j < colliderArray.size(); j++) {
			Collider* cd1 = (Collider*) colliderArray[i]->GetComponent("Collider");
			Collider* cd2 = (Collider*) colliderArray[j]->GetComponent("Collider");

			if(Collision::IsColliding(cd1->box, cd2->box, (PI/180)*colliderArray[i]->angleDeg, (PI/180)*colliderArray[j]->angleDeg)) {
				// COLIDIU
				colliderArray[i]->NotifyCollision(*colliderArray[j]);
				colliderArray[j]->NotifyCollision(*colliderArray[i]);
			}
		}
	}

	colliderArray.clear();

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin()+i);
		}
	}

	if (Alien::alienCount == 0) {
		GameData::playerVictory = true;
		popRequested = true;
		Game& jogo = Game::GetInstance();
		jogo.Push(new EndState());
	}

	if (PenguinBody::player == nullptr) {
		GameData::playerVictory = false;
		popRequested = true;
		Game& jogo = Game::GetInstance();
		jogo.Push(new EndState());
	}
}

void StageState::Render() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->GetComponent("TileMap") != nullptr) {
			objectArray[i]->box.x = Camera::pos.x;
			objectArray[i]->box.y = Camera::pos.y;
		}

		objectArray[i]->Render();
	}
}


void StageState::Pause() {

}

void StageState::Resume() {

}
