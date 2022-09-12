#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {

}

void CameraFollower::Render() {

}

void CameraFollower::Update(float dt) {
	associated.box.x = -1*Camera::pos.x;
	associated.box.y = -1*Camera::pos.y;
}

bool CameraFollower::Is(std::string type) {
	if (type == "CameraFollower" || type == "Camerafollower" || type == "cameraFollower" || type == "camerafollower") {
		return true;
	} else {
		return false;
	}
}
