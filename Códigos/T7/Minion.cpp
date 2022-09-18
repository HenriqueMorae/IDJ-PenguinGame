#include "Minion.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Game.h"
#include "Bullet.h"
#include "Collider.h"
#include "StageState.h"
#include "State.h"

#define PI 3.14159265359

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
	Sprite* sprite = new Sprite(associated, "img/minion.png");
	float escala = 0.75 + (rand() % 101)/200.0;
	sprite->SetScale(escala, escala);
	associated.AddComponent(sprite);

	Collider* collider = new Collider(associated);
	associated.AddComponent(collider);

	this->alienCenter = alienCenter;
	arc = arcOffsetDeg;
	rot = arcOffsetDeg + 90;
	if (rot >= 360) rot -= 360;

	// primeiro valor da box
	if (this->alienCenter.lock() != nullptr) {
		Vec2 objPos = Vec2(150, 0).Rotate((PI/180)*arc) + this->alienCenter.lock()->box.Centro() - Vec2(associated.box.w/2, associated.box.h/2);
		associated.box.x = objPos.x;
		associated.box.y = objPos.y;
		associated.angleDeg = rot;
	} else {
		associated.RequestDelete();
	}
}

void Minion::Boom() {
	State& estado = Game::GetInstance().GetCurrentState();

	GameObject* explosao = new GameObject();
	Sprite* boom = new Sprite(*explosao, "img/miniondeath.png", 4, 0.2, 0.75);
	explosao->AddComponent(boom);
	explosao->box.x = associated.box.Centro().x - boom->GetWidth()/2;
	explosao->box.y = associated.box.Centro().y - boom->GetHeight()/2;
	estado.AddObject(explosao);
}

void Minion::Update(float dt) {
	if (this->alienCenter.lock() != nullptr) {
		arc += 1;
		rot += 1;
		if (arc >= 360) arc -= 360;
		if (rot >= 360) rot -= 360;

		Vec2 objPos = Vec2(150, 0).Rotate((PI/180)*arc) + this->alienCenter.lock()->box.Centro() - Vec2(associated.box.w/2, associated.box.h/2);
		associated.box.x = objPos.x;
		associated.box.y = objPos.y;
		associated.angleDeg = rot;
	} else {
		associated.RequestDelete();
	}
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
	if (type == "Minion" || type == "minion") {
		return true;
	} else {
		return false;
	}
}

void Minion::Shoot(Vec2 target) {
	State& estado = Game::GetInstance().GetCurrentState();

	GameObject* bala = new GameObject();
	bala->box.x = associated.box.Centro().x;
	bala->box.y = associated.box.Centro().y;
	Vec2 direcao = Vec2::Norm(target - associated.box.Centro());
	float dist = Vec2::Dist(target, associated.box.Centro());
	Bullet* bl = new Bullet(*bala, direcao, 200, 1, dist, "img/minionbullet2.png", 3, 0.2, true);
	bala->AddComponent(bl);
	estado.AddObject(bala);
}
