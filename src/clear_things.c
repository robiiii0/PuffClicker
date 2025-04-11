#include "puff.h"


void free_game(game_t *game)
{
    SDL_DestroyTexture(game->texture);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();

    free(game);
}