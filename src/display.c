#include "puff.h"

void run_game(game_t *game)
{
    while (!game->quit)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
            handle_event(event, game);

        if (game->quit)
            break;

        SDL_SetRenderDrawColor(game->renderer, 189, 189, 189, 255);
        SDL_RenderClear(game->renderer);
        // draw everything here
        SDL_RenderCopy(game->renderer, game->puff->texture, NULL, &game->puff->dest_rect);

        // end draw
        SDL_Delay(16);  // ~60 FPS
        SDL_RenderPresent(game->renderer);
    }
}