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
        default:
            break;
    }
    return 0;
}