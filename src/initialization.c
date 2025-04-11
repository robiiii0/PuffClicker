#include "puff.h"



int init_sdl(game_t *game)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        LOG_ERROR("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        LOG_ERROR("Erreur IMG_Init: %s\n", IMG_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }

    // Initialisation du font
    game->font = TTF_OpenFont("assets/font.ttf", 50);
    if (!game->font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
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


int init_player(player_t *player)
{
    player->taffs = 0;
    player->taffs_per_click = 1;
    player->upgrades = 0;

    return 0;
}

int init_game(game_t *game)
{
    if (init_sdl(game))
        return 1;

    game->player = (player_t*)malloc(sizeof(player_t));
    if (init_player(game->player))
        return 1;

    game->quit = false;
    game->puff = load_sprite("assets/vuse.png", game->renderer);
    if (!game->puff) {
        LOG_ERROR("Erreur chargement sprite\n");
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        SDL_Quit();
        return 1;
    }

    return 0;
}