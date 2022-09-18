#include "InputManager.h"
#include "SDL.h"

InputManager& InputManager::GetInstance() {
	static InputManager instance;
	return instance;
}

InputManager::InputManager() {
	for (int i = 0; i < 6; i++) {
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}

	mouseX = 0;
	mouseY = 0;
	quitRequested = false;
	updateCounter = 0;
}

InputManager::~InputManager() {

}

void InputManager::Update() {
	SDL_Event event;

	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested = false;
	updateCounter++;

	while (SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		if(event.type == SDL_MOUSEBUTTONDOWN) {
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}

		if(event.type == SDL_MOUSEBUTTONUP) {
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		}

		if(event.type == SDL_KEYDOWN && event.key.repeat != 1) {
			keyState[event.key.keysym.sym] = true;
			keyUpdate[event.key.keysym.sym] = updateCounter;
		}

		if(event.type == SDL_KEYUP) {
			keyState[event.key.keysym.sym] = false;
			keyUpdate[event.key.keysym.sym] = updateCounter;
		}
	}
}

bool InputManager::KeyPress(int key) {
	if (keyState.count(key) == 1) {
		if (keyState[key] == true && keyUpdate[key] == updateCounter) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool InputManager::KeyRelease(int key) {
	if (keyState.count(key) == 1) {
		if (keyState[key] == false && keyUpdate[key] == updateCounter) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool InputManager::IsKeyDown(int key) {
	if (keyState.count(key) == 1) {
		return keyState[key];
	} else {
		return false;
	}
}

bool InputManager::MousePress(int button) {
	if (button >= 0 && button < 6) {
		if (mouseState[button] == true && mouseUpdate[button] == updateCounter) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool InputManager::MouseRelease(int button) {
	if (button >= 0 && button < 6) {
		if (mouseState[button] == false && mouseUpdate[button] == updateCounter) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool InputManager::IsMouseDown(int button) {
	if (button >= 0 && button < 6) {
		return mouseState[button];
	} else {
		return false;
	}
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}

bool InputManager::QuitRequested() {
	return quitRequested;
}
