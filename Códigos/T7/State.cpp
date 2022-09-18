#include "State.h"

State::State() {
	popRequested = false;
	quitRequested = false;
	started = false;
}

State::~State() {
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* object) {
	std::shared_ptr<GameObject> gameobj(object);
	objectArray.push_back(gameobj);

	if (started) {
		gameobj->Start();
	}

	std::weak_ptr<GameObject> objetoDeJogo(gameobj);

	return objetoDeJogo;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == object) {
			std::weak_ptr<GameObject> objetoDeJogo(objectArray[i]);
			return objetoDeJogo;
		}
	}

	std::weak_ptr<GameObject> objetoDeJogoVazio;

	return objetoDeJogoVazio;
}

bool State::PopRequested() {
	return popRequested;
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::StartArray() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}

	started = true;
}

void State::UpdateArray(float dt) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
}

void State::RenderArray() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}
