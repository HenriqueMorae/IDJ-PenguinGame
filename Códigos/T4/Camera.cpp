#include "Camera.h"
#include "InputManager.h"
#include "SDL.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0,0);
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;
}

void Camera::Unfollow() {
	focus = nullptr;
}

void Camera::Update(float dt) {
	if (focus != nullptr) {
		pos = focus->box.Centro();
	} else {
		float speedX = 0;
		float speedY = 0;

		if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) && InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
			speedX = 0;
		} else if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
			speedX = 500*dt;
		} else if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
			speedX = -500*dt;
		}

		if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) && InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
			speedY = 0;
		} else if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
			speedY = 500*dt;
		} else if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
			speedY = -500*dt;
		}

		speed = Vec2(speedX, speedY);
		pos = pos + speed;
	}
}
