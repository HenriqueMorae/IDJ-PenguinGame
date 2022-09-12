#include "State.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "Collider.h"

#define PI 3.14159265359

State::State() {
	quitRequested = false;
	started = false;

	// Instanciar um um Music
	music = new Music("audio/stageState.ogg");
	music->Volume(32);
	music->Play();
}

State::~State() {
	objectArray.clear();
}

void State::Start() {
	LoadAssets();

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}

	started = true;
}

// Carregar assets
void State::LoadAssets() {
	GameObject* bg = new GameObject();
	Sprite* sprite = new Sprite(*bg, "img/ocean.jpg");
	bg->AddComponent(sprite);
	CameraFollower* cf = new CameraFollower(*bg);
	bg->AddComponent(cf);
	bg->box.x = 0;
	bg->box.y = 0;
	objectArray.emplace_back(bg);

	GameObject* tm = new GameObject();
	TileSet* ts = new TileSet(64, 64, "img/tileset.png");
	TileMap* tilemap = new TileMap(*tm, "map/tileMap.txt", ts);
	tm->AddComponent(tilemap);
	tm->box.x = 0;
	tm->box.y = 0;
	objectArray.emplace_back(tm);

	GameObject* alien = new GameObject();
	Alien* al = new Alien(*alien, 3);
	alien->AddComponent(al);
	Sprite* sp = (Sprite*) alien->GetComponent("Sprite");
	alien->box.x = 512 - sp->GetWidth()/2;
	alien->box.y = 300 - sp->GetHeight()/2;
	objectArray.emplace_back(alien);

	GameObject* pinguim = new GameObject();
	PenguinBody* pb = new PenguinBody(*pinguim);
	pinguim->AddComponent(pb);
	Sprite* sp2 = (Sprite*) pinguim->GetComponent("Sprite");
	pinguim->box.x = 704 - sp2->GetWidth()/2;
	pinguim->box.y = 640 - sp2->GetHeight()/2;
	objectArray.emplace_back(pinguim);
	Camera::Follow(pinguim);
}

void State::Update (float dt) {
	Camera::Update(dt);

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
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

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	std::shared_ptr<GameObject> gameobj(go);
	objectArray.push_back(gameobj);

	if (started) {
		gameobj->Start();
	}

	std::weak_ptr<GameObject> objetoDeJogo(gameobj);

	return objetoDeJogo;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == go) {
			std::weak_ptr<GameObject> objetoDeJogo(objectArray[i]);
			return objetoDeJogo;
		}
	}

	std::weak_ptr<GameObject> objetoDeJogoVazio;

	return objetoDeJogoVazio;
}
