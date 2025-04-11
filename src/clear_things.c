#include "puff.h"

void free_game(game_t *game)
{
    SDL_DestroyTexture(game->texture);
    destroy_sprite(game->puff);
    SDL_DestroyRenderer(game->renderer);

    SDL_DestroyWindow(game->window);
    IMG_Quit();
    SDL_Quit();

    free(game);
}