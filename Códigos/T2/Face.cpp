#include "Face.h"
#include "SDL.h"
#include "Sprite.h"

Face::Face(GameObject& associated) : Component(associated) {
	hitpoints = 30;
	tocandoBOOM = false;
	som = nullptr;
}

void Face::Damage(int damage) {
	hitpoints -= damage;

	if (hitpoints <= 0 && !tocandoBOOM) {
		som = (Sound*) associated.GetComponent("Sound");
		Sprite* sprite = (Sprite*) associated.GetComponent("Sprite");
		if (som != nullptr) {
			som->Play();
			associated.RemoveComponent(sprite);
			tocandoBOOM = true;
		}
	}
}

void Face::Update(float dt) {
	if (tocandoBOOM) {
		if (!som->IsPlaying()) {
			associated.RequestDelete();
		}
	}
}

void Face::Render() {

}

bool Face::Is(std::string type) {
	if (type == "Face" || type == "face") {
		return true;
	} else {
		return false;
	}
}
