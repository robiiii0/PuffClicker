
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define LOG_INFO(...) fprintf(stdout, __VA_ARGS__)

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct player_s {
    float taffs;
    float taffs_per_click;
    int upgrades;
    float taffs_per_second;
} player_t;

typedef struct {
    SDL_Texture *texture;
    SDL_Rect dest_rect;
} sprite_t;

typedef struct game_s {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    TTF_Font *font;

    sprite_t *puff;

    player_t *player;

    bool quit;
} game_t;



int init_game(game_t *game);
void run_game(game_t *game);
void free_game(game_t *game);
int handle_event(SDL_Event event, game_t *game);
sprite_t *load_sprite(const char *filepath, SDL_Renderer *renderer);
void destroy_sprite(sprite_t *sprite);
