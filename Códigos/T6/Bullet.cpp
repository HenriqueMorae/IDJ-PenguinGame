#include <cmath>
#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"

#define PI 3.14159265359

Bullet::Bullet(GameObject& associated, Vec2 direcao, float speed, int damage, float maxDistance, std::string sprite, int frames, float tempo, bool tP) : Component(associated) {
	Sprite* sp = new Sprite(associated, sprite, frames, tempo);
	associated.AddComponent(sp);
	associated.box.x -= sp->GetWidth()/2;
	associated.box.y -= sp->GetHeight()/2;

	Collider* collider = new Collider(associated);
	associated.AddComponent(collider);

	this->speed = Vec2::Mult(direcao, speed);
	this->damage = damage;
	distanceLeft = maxDistance;

	float angulo = asin(direcao.y)*(180/PI);
	if(direcao.x < 0) {
		sp->SetFlip((SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
		angulo *= -1;
	}
	associated.angleDeg = angulo;
	targetsPlayer = tP;
	jaDeiDano = false;
}

void Bullet::Update(float dt) {
	Vec2 speedFrame = Vec2::Mult(speed, dt);

	associated.box.x += speedFrame.x;
	associated.box.y += speedFrame.y;

	distanceLeft -= Vec2::Mag(speedFrame);

	if (distanceLeft <= 0) {
		associated.RequestDelete();
	}
}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {
	if (type == "Bullet" || type == "bullet") {
		return true;
	} else {
		return false;
	}
}

int Bullet::GetDamage() {
	if (!jaDeiDano) {
		jaDeiDano = true;
		return damage;
	} else {
		return 0;
	}
}

bool Bullet::GetTarget() {
	return targetsPlayer;
}
