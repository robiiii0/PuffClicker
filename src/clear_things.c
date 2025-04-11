#include "puff.h"

void free_game(game_t *game)
{
    free(game->player);

    TTF_CloseFont(game->font);
    TTF_CloseFont(game->upgrade_font);

    SDL_DestroyTexture(game->texture);
    destroy_sprite(game->puff);
    SDL_DestroyRenderer(game->renderer);

    SDL_DestroyWindow(game->window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    free(game);
}