#define SDL_MAIN_HANDLED
#include "Game.h"

int main(int argc, char* args[]) {

    Game game;

    Game::ShowControlsAndCredits();

    if (!game.Initialize()) {
        return 1;
    }

    game.Run();

    return 0;
}