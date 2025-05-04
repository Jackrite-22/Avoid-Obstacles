#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    if (game.init("Avoid Obstacles", 800, 600)) {
        game.run();
    }
    game.clean();
    return 0;
}


