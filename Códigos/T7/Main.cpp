#include "Game.h"
#include "TitleState.h"

int main (int argc, char** argv) {
	Game& jogo = Game::GetInstance();
	jogo.Push(new TitleState());
	jogo.Run();

    return 0;
}
