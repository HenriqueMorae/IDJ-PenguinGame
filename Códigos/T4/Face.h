#include <string>
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"

#ifndef FACE_H
#define FACE_H

// Classe "Face" que eh um inimigo com uma quantidade de HP
// COMPONENT
class Face : public Component {
	private:
		int hitpoints;
		bool tocandoBOOM;
		Sound* som;

	public:
		Face(GameObject& associated);
		void Damage(int damage);
		void Update(float dt);
		void Render();
		bool Is(std::string type);
};

#endif // FACE_H
