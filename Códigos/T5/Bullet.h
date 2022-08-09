#include "Component.h"
#include "GameObject.h"

#ifndef BULLET_H
#define BULLET_H

// Classe "Bullet"
// COMPONENT
class Bullet : public Component {
	private:
		Vec2 speed;
		float distanceLeft;
		int damage;

	public:
		Bullet(GameObject& associated, Vec2 direcao, float speed, int damage, float maxDistance, std::string sprite);
		void Update(float dt);
		void Render();
		bool Is(std::string type);
		int GetDamage();
};

#endif // BULLET_H
