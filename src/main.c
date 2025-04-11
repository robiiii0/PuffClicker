
#include "puff.h"


int main(int argc, char *argv[])
{

    game_t *game = (game_t*)malloc(sizeof(game_t));

    if (init_game(game) != 0) {
        LOG_ERROR("Erreur d'initialisation du jeu\n");
        return 1;
    }

    run_game(game);

    free_game(game);

    return 0;
}