#include "Game.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
	if (instance == nullptr) {
		instance = new Game("Henrique Moraes - 180033000", 1024, 600);
	}

	return *instance;
}

Game::Game (std::string title, int width, int height) {
	if (instance == nullptr) {
		instance = this;
	}

	// Inicializando SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		std::abort();
	}

	// Inicializando SDL_Image
	int imgflags = IMG_INIT_JPG | IMG_INIT_PNG;
	int imginiciados = IMG_Init(imgflags);
	if ((imginiciados&imgflags) != imgflags) {
		SDL_Log("Unable to initialize IMG: %s", IMG_GetError());
		std::abort();
	}

	// Inicializando SDL_mixer
	int mixflags = MIX_INIT_MP3 | MIX_INIT_OGG;
	int mixiniciados = Mix_Init(mixflags);
	if ((mixiniciados&mixflags) != mixflags) {
		SDL_Log("Unable to initialize Mix: %s", Mix_GetError());
		std::abort();
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
		SDL_Log("Unable to initialize Mix: %s", Mix_GetError());
		std::abort();
	}
	Mix_AllocateChannels(32);

	// Inicializar janela
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == nullptr) {
		SDL_Log("Unable to initialize Window: %s", SDL_GetError());
		std::abort();
	}

	// Incializar renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_Log("Unable to initialize Renderer: %s", SDL_GetError());
		std::abort();
	}

	// Instanciar um State
	state = new State();
}

Game::~Game() {
	// Deletar State
	delete state;

	// Deletar renderer e janela
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Deletar SDL_mixer
	Mix_CloseAudio();
	Mix_Quit();

	// Deletar SDL_Image
	IMG_Quit();

	// Deletar SDL
	SDL_Quit();
}

State& Game::GetState() {
	return *state;
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

// Game Loop
void Game::Run() {
	while (!state->QuitRequested()) {
		state->Update(1.0f);
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}
