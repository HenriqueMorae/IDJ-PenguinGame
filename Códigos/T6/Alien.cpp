#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"
#include "State.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "PenguinBody.h"

int Alien::alienCount;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	Sprite* sprite = new Sprite(associated, "img/alien.png");
	associated.AddComponent(sprite);
	Collider* collider = new Collider(associated);
	associated.AddComponent(collider);

	hp = nMinions;
	speed.x = 200;
	speed.y = 200;
	rot = 0;

	alienCount++;
	state = RESTING;
}

void Alien::Start() {
	// colocar Minions
	State& estado = Game::GetInstance().GetState();

	GameObject* minion1 = new GameObject();
	Minion* mn = new Minion(*minion1, estado.GetObjectPtr(&associated), 0);
	minion1->AddComponent(mn);
	minionArray.push_back(estado.AddObject(minion1));

	GameObject* minion2 = new GameObject();
	Minion* mn2 = new Minion(*minion2, estado.GetObjectPtr(&associated), 120);
	minion2->AddComponent(mn2);
	minionArray.push_back(estado.AddObject(minion2));

	GameObject* minion3 = new GameObject();
	Minion* mn3 = new Minion(*minion3, estado.GetObjectPtr(&associated), 240);
	minion3->AddComponent(mn3);
	minionArray.push_back(estado.AddObject(minion3));
}

Alien::~Alien() {
	minionArray.clear();
	alienCount--;
}

void Alien::Update(float dt) {
	switch (state) {
		case RESTING: {
			restTimer.Update(dt);
			if (restTimer.Get() >= 1) {
				restTimer.Restart();
				if (PenguinBody::player != nullptr) {
					destination.x = PenguinBody::player->Position().x;
					destination.y = PenguinBody::player->Position().y;
					direcao = Vec2::Norm(destination - associated.box.Centro()) * speed;
					state = MOVING;
				}
			}
			break;
		}
		case MOVING: {
			if (Vec2::Dist(destination,associated.box.Centro()) <= Vec2::Mag(direcao)*dt) {
				associated.box.x = destination.x - associated.box.w/2;
				associated.box.y = destination.y - associated.box.h/2;

				if (PenguinBody::player != nullptr) {
					destination.x = PenguinBody::player->Position().x;
					destination.y = PenguinBody::player->Position().y;

					std::shared_ptr<GameObject> minionEscolhido = minionArray[0].lock();

					for (unsigned int i = 0; i < minionArray.size(); i++) {
						if (Vec2::Dist(minionArray[i].lock()->box.Centro(), destination) < Vec2::Dist(minionEscolhido->box.Centro(), destination)) {
							minionEscolhido = minionArray[i].lock();
						}
					}

					Minion* cptMn = (Minion*) minionEscolhido->GetComponent("Minion");
					cptMn->Shoot(destination);
				}
				state = RESTING;
			} else {
				associated.box.x += direcao.x*dt;
				associated.box.y += direcao.y*dt;
			}
			break;
		}
		default: break;
	}

	rot -= 0.5;
	if (rot < 0) rot += 360;
	associated.angleDeg = rot;
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
	if (type == "Alien" || type == "alien") {
		return true;
	} else {
		return false;
	}
}

void Alien::NotifyCollision(GameObject& other) {
	if (other.GetComponent("Bullet") != nullptr) {
		Bullet* bl = (Bullet*) other.GetComponent("Bullet");

		if (!bl->GetTarget()) {
			hp -= bl->GetDamage();
			other.RequestDelete();

			if (hp <= 0) {
				State& estado = Game::GetInstance().GetState();

				GameObject* explosao = new GameObject();
				Sprite* boom = new Sprite(*explosao, "img/aliendeath.png", 4, 0.2, 0.8);
				explosao->AddComponent(boom);
				explosao->box.x = associated.box.Centro().x - boom->GetWidth()/2;
				explosao->box.y = associated.box.Centro().y - boom->GetHeight()/2;
				Sound* som = new Sound(*explosao, "audio/boom.wav");
				som->Volume(64);
				som->Play();
				explosao->AddComponent(som);
				estado.AddObject(explosao);

				associated.RequestDelete();
			}
		}
	}
}
