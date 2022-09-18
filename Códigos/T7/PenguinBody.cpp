#include "PenguinBody.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
#include "Camera.h"
#include "Bullet.h"
#include "Sound.h"

#define PI 3.14159265359

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
	speed.x = 0;
	speed.y = 0;
	linearSpeed = 0;
	angle = 0;
	hp = 5;

	Sprite* sprite = new Sprite(associated, "img/penguin.png");
	associated.AddComponent(sprite);

	Collider* collider = new Collider(associated);
	associated.AddComponent(collider);

	player = this;
}

PenguinBody::~PenguinBody() {
	player = nullptr;
}

void PenguinBody::Start() {
	State& estado = Game::GetInstance().GetCurrentState();

	GameObject* canhao = new GameObject();
	PenguinCannon* pc = new PenguinCannon(*canhao, estado.GetObjectPtr(&associated));
	canhao->AddComponent(pc);
	Sprite* sp = (Sprite*) canhao->GetComponent("Sprite");
	canhao->box.x = associated.box.Centro().x - sp->GetWidth()/2;
	canhao->box.y = associated.box.Centro().y - sp->GetHeight()/2;
	pcannon = estado.AddObject(canhao);
}

void PenguinBody::Update(float dt) {
	if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
		linearSpeed += 20;
		if (linearSpeed > 300) linearSpeed = 300;
	}

	if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
		linearSpeed -= 20;
		if (linearSpeed < -300) linearSpeed = -300;
	}

	if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
		angle -= 5;
		if (angle < 0) angle += 360;
	}

	if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
		angle += 5;
		if (angle >= 360) angle -= 360;
	}

	speed = Vec2(linearSpeed, 0).Rotate((PI/180)*angle);

	associated.box.x += speed.x * dt;
	pcannon.lock()->box.x += speed.x * dt;
	associated.box.y += speed.y * dt;
	pcannon.lock()->box.y += speed.y * dt;
	associated.angleDeg = angle;

	if (associated.box.Centro().x < 0) {
		associated.box.x -= speed.x * dt;
		pcannon.lock()->box.x -= speed.x * dt;
	}

	if (associated.box.Centro().y < 0) {
		associated.box.y -= speed.y * dt;
		pcannon.lock()->box.y -= speed.y * dt;
	}

	if (associated.box.Centro().x > 1408) {
		associated.box.x -= speed.x * dt;
		pcannon.lock()->box.x -= speed.x * dt;
	}

	if (associated.box.Centro().y > 1280) {
		associated.box.y -= speed.y * dt;
		pcannon.lock()->box.y -= speed.y * dt;
	}
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(std::string type) {
	if (type == "PenguinBody" || type == "penguinbody" || type == "Penguinbody" || type == "penguinBody") {
		return true;
	} else {
		return false;
	}
}

void PenguinBody::NotifyCollision(GameObject& other) {
	if (other.GetComponent("Bullet") != nullptr) {
		Bullet* bl = (Bullet*) other.GetComponent("Bullet");

		if (bl->GetTarget()) {
			hp -= bl->GetDamage();
			other.RequestDelete();

			if (hp <= 0) {
				Camera::Unfollow();

				State& estado = Game::GetInstance().GetCurrentState();

				GameObject* explosao = new GameObject();
				Sprite* boom = new Sprite(*explosao, "img/penguindeath.png", 5, 0.2, 1);
				explosao->AddComponent(boom);
				explosao->box.x = associated.box.Centro().x - boom->GetWidth()/2;
				explosao->box.y = associated.box.Centro().y - boom->GetHeight()/2;
				Sound* som = new Sound(*explosao, "audio/boom.wav");
				som->Volume(64);
				som->Play();
				explosao->AddComponent(som);
				estado.AddObject(explosao);

				associated.RequestDelete();
				pcannon.lock()->RequestDelete();
			}
		}
	}
}

Vec2 PenguinBody::Position() {
	return associated.box.Centro();
}
