#include <string>
#include "Component.h"
#include "GameObject.h"

#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

// Classe "Camera Follower"
// COMPONENT
class CameraFollower : public Component {
	public:
		CameraFollower(GameObject& go);
		void Render();
		void Update(float dt);
		bool Is(std::string type);
};

#endif // CAMERAFOLLOWER_H
