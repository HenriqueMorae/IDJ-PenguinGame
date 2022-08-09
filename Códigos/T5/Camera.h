#include "GameObject.h"
#include "Vec2.h"

#ifndef CAMERA_H
#define CAMERA_H

// Classe "Camera" que controla a camera
class Camera {
	private:
		static GameObject* focus;

	public:
		static Vec2 pos;
		static Vec2 speed;

		static void Follow(GameObject* newFocus);
		static void Unfollow();
		static void Update(float dt);
};

#endif // CAMERA_H
