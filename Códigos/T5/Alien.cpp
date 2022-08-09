#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"
#include "State.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
	Sprite* sprite = new Sprite(associated, "img/alien.png");
	associated.AddComponent(sprite);

	hp = nMinions;
	speed.x = 200;
	speed.y = 200;
	rot = 0;
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
}

void Alien::Update(float dt) {
	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		taskQueue.push(Action(Action::SHOOT, InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y));
	}

	if(InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT)) {
		taskQueue.push(Action(Action::MOVE, InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y));
	}

	if (taskQueue.size() > 0) {
		Action acao = taskQueue.front();

		switch (acao.type) {
			case Action::MOVE: {
				Vec2 direcao = Vec2::Norm(acao.pos - associated.box.Centro()) * speed;
				if (Vec2::Dist(acao.pos,associated.box.Centro()) < Vec2::Mag(direcao)*dt) {
					associated.box.x = acao.pos.x - associated.box.w/2;
					associated.box.y = acao.pos.y - associated.box.h/2;
					taskQueue.pop();
				} else {
					associated.box.x += direcao.x*dt;
					associated.box.y += direcao.y*dt;
				}
				break;
			}
			case Action::SHOOT: {
				std::shared_ptr<GameObject> minionEscolhido = minionArray[0].lock();

				for (unsigned int i = 0; i < minionArray.size(); i++) {
					if (Vec2::Dist(minionArray[i].lock()->box.Centro(), acao.pos) < Vec2::Dist(minionEscolhido->box.Centro(), acao.pos)) {
						minionEscolhido = minionArray[i].lock();
					}
				}

				Minion* cptMn = (Minion*) minionEscolhido->GetComponent("Minion");
				cptMn->Shoot(acao.pos);
				taskQueue.pop();
				break;
			}
			default: break;
		}
	}

	if (hp <= 0) {
		associated.RequestDelete();
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
