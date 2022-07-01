#include <vector>
#include <string>
#include <memory>
#include "Rect.h"
#include "Component.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// Classe "GameObject"
class GameObject {
	private:
		std::vector<std::unique_ptr<Component>> components;
		bool isDead;

	public:
		Rect box;

		GameObject();
		~GameObject();
		void Update(float dt);
		void Render();
		bool IsDead();
		void RequestDelete();
		void AddComponent(Component* cpt);
		void RemoveComponent(Component* cpt);
		Component* GetComponent(std::string type);
};

#endif // GAMEOBJECT_H
