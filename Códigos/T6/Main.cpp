#include "Game.h"

int main (int argc, char** argv) {
	Game& jogo = Game::GetInstance();
	jogo.Run();

    return 0;
}
