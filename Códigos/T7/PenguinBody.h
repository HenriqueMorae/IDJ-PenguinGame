#include <memory>
#include "Component.h"
#include "Vec2.h"

#ifndef PENGUINBODY_H
#define PENGUINBODY_H

// Classe "PenguinBody"
// COMPONENT
class PenguinBody : public Component {
	private:
		std::weak_ptr<GameObject> pcannon;
		Vec2 speed;
		float linearSpeed;
		float angle;
		int hp;

	public:
		PenguinBody(GameObject& associated);
		~PenguinBody();
		void Start();
		void Update(float dt);
		void Render();
		bool Is(std::string type);
		static PenguinBody* player;
		void NotifyCollision(GameObject& other);
		Vec2 Position();
};

#endif // PENGUINBODY_H
