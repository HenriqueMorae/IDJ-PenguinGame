#include "Collider.h"
#include "GameObject.h"

// #define DEBUG

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"
#include "SDL.h"
#endif // DEBUG

#define PI 3.14159265359

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
	this->scale = scale;
	this->offset = offset;
}

void Collider::Update(float dt) {
	box.h = scale.y*associated.box.h;
	box.w = scale.x*associated.box.w;
	box.x = associated.box.Centro().x - box.w/2 + offset.Rotate((PI/180)*associated.angleDeg).x;
	box.y = associated.box.Centro().y - box.h/2 + offset.Rotate((PI/180)*associated.angleDeg).y;
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center(box.Centro());
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).Rotate(associated.angleDeg/(180/PI)) + center + Camera::pos;

	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y) - center).Rotate(associated.angleDeg/(180/PI)) + center + Camera::pos;
	points[1] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate(associated.angleDeg/(180/PI)) + center + Camera::pos;
	points[2] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x, box.y + box.h) - center).Rotate(associated.angleDeg/(180/PI)) + center + Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type) {
	if (type == "Collider" || type == "collider") {
		return true;
	} else {
		return false;
	}
}

void Collider::SetScale(Vec2 scale) {
	this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
	this->offset = offset;
}
