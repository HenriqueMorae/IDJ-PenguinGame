#include "State.h"
#include "Face.h"
#include "Sound.h"
#include "Sprite.h"

#define PI 3.14159265359

State::State() {
	quitRequested = false;

	GameObject* bg = new GameObject();
	Sprite* sprite = new Sprite(*bg, "img/ocean.jpg");
	bg->AddComponent(sprite);
	bg->box.x = 0;
	bg->box.y = 0;
	objectArray.emplace_back(bg);

	// Instanciar um um Music
	music = new Music("audio/stageState.ogg");
	music->Volume(32);
	music->Play();
}

State::~State() {
	objectArray.clear();
}

// Carregar assets
void State::LoadAssets() {

}

void State::Update (float dt) {
	Input();

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin()+i);
		}
	}
}

void State::Render() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrario
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminacao
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de tras pra frente pra sempre clicar no objeto mais de cima
			for (int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();

				// Nota: Desencapsular o ponteiro eh algo que devemos evitar ao maximo.
				// O proposito do unique_ptr eh manter apenas uma copia daquele ponteiro,
				// ao usar get(), violamos esse principio e estamos menos seguros.
				// Esse codigo, assim como a classe Face, eh provisorio. Futuramente, para
				// chamar funcoes de GameObjects, use objectArray[i]->funcao() direto.

				if(go->box.EstaDentro({(float)mouseX, (float)mouseY})) {

					Face* face = (Face*) go->GetComponent("Face");
					if (nullptr != face) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (so queremos acertar um)
						break;
					}

				}
			}
		}

		if(event.type == SDL_KEYDOWN) {
			// Se a tecla for ESC, setar a flag de quit
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				quitRequested = true;
			}
			// Se nao, crie um objeto
			else {
				Vec2 objPos = Vec2(200, 0).Rotate(-PI + PI*(rand() % 1001)/500.0) + Vec2(mouseX, mouseY);
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY) {
	GameObject* pinguim = new GameObject();
	Sprite* sprite = new Sprite(*pinguim, "img/penguinface.png");
	pinguim->AddComponent(sprite);
	pinguim->box.x = mouseX - sprite->GetWidth()/2;
	pinguim->box.y = mouseY - sprite->GetHeight()/2;
	Sound* som = new Sound(*pinguim, "audio/boom.wav");
	som->Volume(64);
	pinguim->AddComponent(som);
	Face* face = new Face(*pinguim);
	pinguim->AddComponent(face);
	objectArray.emplace_back(pinguim);
}
