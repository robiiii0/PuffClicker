#include "puff.h"


void run_game(game_t *game)
{
    while (!game->quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event))
            handle_event(event, game);

        if (game->quit)
            break;

        SDL_SetRenderDrawColor(game->renderer, 189, 189, 189, 255);
        SDL_RenderClear(game->renderer);
        // draw everything here

        // end draw
        SDL_RenderPresent(game->renderer);
    }
}