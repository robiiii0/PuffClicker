#include "puff.h"



int init_sdl(game_t *game)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        LOG_ERROR("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création d'une fenêtre
    game->window = SDL_CreateWindow(
        "GAME",                            // Title
        SDL_WINDOWPOS_CENTERED,            // Pos X
        SDL_WINDOWPOS_CENTERED,            // Pos Y
        SCREEN_WIDTH,                      // Width
        SCREEN_HEIGHT,                     // Height
        0                                  // Options
    );

    if (game->window == NULL) {
        LOG_ERROR("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    game->renderer = SDL_CreateRenderer(
        game->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    game->texture = SDL_CreateTexture(
            game->renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            SCREEN_WIDTH,
            SCREEN_HEIGHT
    );
    return 0;
}


int init_game(game_t *game)
{
    if (init_sdl(game))
        return 1;

    game->quit = false;

    return 0;
}