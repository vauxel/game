#include "game.h"

int main(void) {
	Game* game = Game::instance();
	game->init();

	if (game->initialized) {
		game->loop();
	}

	return 0;
}