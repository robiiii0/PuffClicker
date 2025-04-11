#include "puff.h"

int handle_event(SDL_Event event, game_t *game)
{
    int key;
    switch (event.type) {
        case SDL_QUIT:
            game->quit = true;
            break;
        case SDL_KEYDOWN:
            key = event.key.keysym.sym;
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Si un clic gauche (bouton 1) est effectué
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;

                // Vérifie si le clic est dans la zone de l'image
                if (mouse_x >= game->puff->dest_rect.x &&
                    mouse_x <= game->puff->dest_rect.x + game->puff->dest_rect.w &&
                    mouse_y >= game->puff->dest_rect.y &&
                    mouse_y <= game->puff->dest_rect.y + game->puff->dest_rect.h) {
                    // Incrémenter les "taffs" (actions de clic)
                    game->player->taffs += game->player->taffs_per_click;
                    game->puff_anim_start = SDL_GetTicks();
                    game->puff_animating = true;
                }
            }
            break;
        default:
            break;
    }
    return 0;
}