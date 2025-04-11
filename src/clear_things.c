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

Uint32 last_time = 0;  // Dernier temps en millisecondes

void update_delta_time(game_t* game) {
    Uint32 current_time = SDL_GetTicks();  // Obtient le temps actuel en millisecondes
    game->delta_time = (current_time - last_time) / 1000.0f;  // Convertir en secondes
    last_time = current_time;  // Mettre à jour le dernier temps
}