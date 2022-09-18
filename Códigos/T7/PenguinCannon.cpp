#include <cmath>
#include "PenguinCannon.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Bullet.h"
#include "Collider.h"
#include "StageState.h"

#define PI 3.14159265359

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
	pbody = penguinBody;
	angle = 0;
	direcao.x = 0;
	direcao.y = 0;
	mouse.x = 0;
	mouse.y = 0;

	Sprite* sprite = new Sprite(associated, "img/cubngun.png");
	associated.AddComponent(sprite);

	Collider* collider = new Collider(associated);
	associated.AddComponent(collider);

	tempo = new Timer();
	tempo->Update(2);
}

void PenguinCannon::Update(float dt) {
	tempo->Update(dt);

	if (pbody.lock() != nullptr) {
		mouse = Vec2(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y);
		direcao = Vec2::Norm(mouse - associated.box.Centro());

		angle = asin(direcao.y)*(180/PI);
		if(direcao.x < 0) {
			Sprite* sp = (Sprite*) associated.GetComponent("Sprite");
			sp->SetFlip((SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
			angle *= -1;
		} else if (direcao.x > 0) {
			Sprite* sp = (Sprite*) associated.GetComponent("Sprite");
			sp->SetFlip((SDL_RendererFlip)(SDL_FLIP_NONE));
		}
		associated.angleDeg = angle;

		if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
			if (tempo->Get() >= 1) {
				Shoot();
				tempo->Restart();
			}
		}
	} else {
		associated.RequestDelete();
	}
}

void PenguinCannon::Shoot() {
	State& estado = Game::GetInstance().GetCurrentState();

	GameObject* bala = new GameObject();
	bala->box.x = associated.box.Centro().x + direcao.x*50;
	bala->box.y = associated.box.Centro().y + direcao.y*50;
	float dist = Vec2::Dist(mouse, associated.box.Centro());
	Bullet* bl = new Bullet(*bala, direcao, 400, 1, dist-50, "img/penguinbullet.png", 4, 0.2, false);
	bala->AddComponent(bl);
	estado.AddObject(bala);
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) {
	if (type == "PenguinCannon" || type == "penguincannon" || type == "Penguincannon" || type == "penguinCannon") {
		return true;
	} else {
		return false;
	}
}
