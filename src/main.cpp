#include "game.h"

int main(void) {
    Game* game = new Game();
    
    if(game->initialized) {
        game->loop();
    }

    delete game;
	return 0;
}